#include<iostream>
#include<vector>
using namespace std;

struct node { int order = 0, low = 0, cpn = 0; }; //順序、可追朔的最小點、所屬的component編號
vector<vector<int>>graph; //有向圖
vector<node>point; //記錄每一點的狀態
vector<int>inStack; //用vector模擬stack來暫存在dfs時所經過的點
int cpnNum = 0; //component編號，最後的值可當作component數

void dfs_strong_connect_component(int cur, int& time)
{
	point[cur].order = point[cur].low = time++; //每次先做順序記號代表已走過
	inStack.push_back(cur); //每次先將當前的點放入stack
	for (int x = 0; x < graph[cur].size(); x++)
	{
		if (point[graph[cur][x]].order) //如果下一個要走訪的order不是0，代表下一個點已走訪過
		{
			for (int i = 0; i < inStack.size(); i++)
			{
				if (inStack[i] == graph[cur][x]) //若下個點有在stack裡面，代表可形成component(即有向圖的環)
				{
					point[cur].low = min(point[cur].low, point[graph[cur][x]].order); //若下一個要走訪的節點編號較小，則將其值給當前的low
					break;
				}
			}
		}
		else
		{
			dfs_strong_connect_component(graph[cur][x], time); //反之代表下一個點還沒走訪過，繼續跑dfs
			point[cur].low = min(point[cur].low, point[graph[cur][x]].low); //若當前的點low值較大，則將其改成child的low值
		}
	}

	if (point[cur].order == point[cur].low) //最後檢查，若條件成立，代表此點是cut point
	{
		int temp; //暫存
		do
		{
			temp = inStack.back(); //每次紀錄stack的top
			inStack.pop_back(); //stack先pop
			point[temp].cpn = cpnNum; //將每組component編號(從0開始)，將同編號的點視為一點(即縮點的概念)
		} while (temp != cur); //一直pop到最後pop出來的是cut point，過程中所pop出來的元素皆為同個component
		cpnNum++;
	}
}

int main()
{
	int testCase, caseNum = 1, light, link, ans = 0; //測資數、當前測資編號、點、邊、答案
	cin >> testCase;
	for (vector<bool>component; testCase--; cpnNum = ans = 0)
	{
		cin >> light >> link;
		graph.assign(light + 1, vector<int>()); //0不用
		point.assign(light + 1, node()); //0不用
		for (int start, end; link--;) //建有向圖
		{
			cin >> start >> end;
			graph[start].push_back(end);
		}

		for (int time, y = 1; y < graph.size(); y++) //找形成環的component
		{
			if (point[y].order == 0)
			{
				dfs_strong_connect_component(y, time = 1);
			}
		}

		component.assign(cpnNum, true); //最後cpnNum的值== component的數量，以此建立陣列大小(預設全設true，即預設當前所有點都可當作起始點)
		for (int y = 1; y < graph.size(); y++) //檢查所有當前的點指向另一點
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				if (point[y].cpn != point[graph[y][x]].cpn) //若2點間所屬的component編號不同
				{
					//代表目標點(graph[y][x])的component處於"被接入"狀態，故目標component中的任意點不能當作推骨牌時的"起始點"
					component[point[graph[y][x]].cpn] = false; //e.x :設2者cpn編號為1和2。若條件成立，代表存在1 → 2，若推倒1中的任意點，則2也會被影響
				}
			}
		}

		for (int i = 0; i < component.size(); i++) //最後計算有多少component可當作起始點
		{
			if (component[i]) //若為true則代表可當作起始點
			{
				ans++;
			}
		}

		cout << "Case " << caseNum++ << ": " << ans << endl;
	}

	system("pause");
}