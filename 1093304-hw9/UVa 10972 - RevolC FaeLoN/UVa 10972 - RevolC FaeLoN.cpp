#include<iostream>
#include<vector>
using namespace std;

struct node { int order = 0, low = 0, cpn = 0; }; //順序、可追朔的最小點、所屬的component編號
vector<vector<int>>graph; //無向圖
vector<node>point; //記錄每一點的狀態
vector<int>inStack; //用vector模擬stack來暫存在dfs時所經過的點
int cpnNum = 0; //component編號，最後的值可當作component數

void dfs_bridge_component(int cur, int par, int& time)
{
	point[cur].order = point[cur].low = time++; //每次先做順序記號代表已走過
	inStack.push_back(cur); //每次先將當前的點放入stack
	for (int x = 0; x < graph[cur].size(); x++) //檢查和當前連接的所有點
	{
		if (graph[cur][x] != par) //若接下來要走訪的點不是parent(若此if不檢查、則會把cur和par間的連結當成back edge而導致錯誤)
		{
			if (point[graph[cur][x]].order == 0) //如果下一個要走訪的order是0
			{
				dfs_bridge_component(graph[cur][x], cur, time); //代表下一個點還沒走訪過，繼續跑dfs
			}

			//若當前的點low值較大，則將其low值改成child的low值，反之同理。總之就是2者的low盡可能互相取最小
			(point[cur].low > point[graph[cur][x]].low) ? (point[cur].low = point[graph[cur][x]].low) : (point[graph[cur][x]].low = point[cur].low);
		}
	}

	if (point[cur].order == point[cur].low) //最後檢查，若條件成立，代表此點是bridge
	{
		int temp; //暫存
		do
		{
			temp = inStack.back(); //每次紀錄stack的top
			inStack.pop_back(); //stack先pop
			point[temp].cpn = cpnNum; //將每組component編號(從0開始)，將同編號的點視為一點(即縮點的概念)
		} while (temp != cur); //一直pop到最後出來的是cut point，過程中所pop出來的元素皆為同個component
		cpnNum++;
	}
}

int main()
{
	vector<int>component;
	for (int nodeNum, road; cin >> nodeNum >> road; cpnNum = 0) //點、邊；每次初始化
	{
		graph.assign(nodeNum + 1, vector<int>()); //0不用
		point.assign(nodeNum + 1, node()); //0不用
		for (int x, y; road--;) //建無向圖
		{
			cin >> y >> x;
			graph[y].push_back(x);
			graph[x].push_back(y);
		}

		for (int time, y = 1; y < graph.size(); y++) //找bridge component
		{
			if (point[y].order == 0)
			{
				dfs_bridge_component(y, y, time = 1); //代表該點還沒有走過，以此為root跑dfs找bridge component
			}
		}

		if (cpnNum == 1) //若只有1個component
		{
			cout << 0 << endl; //則無向改成有向圖後，不需要額外加道路
			continue;
		}

		component.assign(cpnNum, 0); //以cpnNum建立陣列大小，value代表所有點(component縮點)與其他點有幾條連接
		for (int y = 1; y < graph.size(); y++)
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				if (point[y].cpn != point[graph[y][x]].cpn) //若2點間所屬的component編號不同
				{
					component[point[y].cpn]++; //代表當前的component有連出去1條邊，故 + 1
				}
			}
		}

		int alonePoint = 0, leaf = 0; //單獨點(沒有與其他連接的component也算在內)，葉子節點
		for (int i = 0; i < component.size(); i++)
		{
			switch (component[i]) //對於所有的component
			{
			case 0: //若為0，代表為單獨點
				alonePoint++;
				break;
			case 1: //若為1，代表為葉子節點
				leaf++;
			}
		}

		//對於1顆樹，若leaf == 2，則需要1條邊將2點連成環、若leaf == 3，則需要2條邊將3點連成環，故為(leaf + 1) / 2
		//對於1個點，可視為將點插入某顆樹中的邊，則邊會分成2條，可將其中1條當成alonePoint所提供，故alonePoint不需*2
		cout << (leaf + 1) / 2 + alonePoint << endl;
	}

	system("pause");
}