#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct node { int order = 0, low = 0; }; //每個節點紀錄順序，及一個可追朔到最遠並形成環的祖先
vector<vector<int>>graph; //無向圖
vector<node>point; //記錄每一點的狀態
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> output; //若first同，則會比較second，排序方式為頂端值最小

void dfs_find_bridge(int cur, int par, int& time) //current、parent、順序記號(可將cur和par間的橋視為cur的一部分)
{
	point[cur].order = point[cur].low = time++; //每次先做順序記號代表已走過
	for (int x = 0; x < graph[cur].size(); x++) //檢查和當前連接的所有點
	{
		if (graph[cur][x] != par) //若接下來要走訪的點不是parent(若此if不檢查、則會把cur和par間的連結當成back edge而導致錯誤)
		{
			if (point[graph[cur][x]].order == 0) //如果下一個要走訪的order是0
			{
				dfs_find_bridge(graph[cur][x], cur, time); //代表下一個點還沒走訪過，繼續跑dfs
			}

			//若當前的點low值較大，則將其low值改成child的low值，反之同理。總之就是2者的low盡可能互相取最小
			(point[cur].low > point[graph[cur][x]].low) ? (point[cur].low = point[graph[cur][x]].low) : (point[graph[cur][x]].low = point[cur].low);
		}
	}

	if (cur != par && point[cur].order == point[cur].low) //若非root且cur的order == low，代表cur沒有任何子代有連到par之前而形成環
	{
		output.push({ min(cur, par),max(cur, par) }); //cur和par間的連結為橋，題求點的編號由小到大，若第1個點編號相同則以比第2個點由小到大
	}
}

int main()
{
	char buf; //輸入括號用
	for (int nodeNum; cin >> nodeNum; cout << endl, graph.clear(), point.clear()) //點個數；每次資料重置
	{
		graph.resize(nodeNum); //使用0，因題目有編號為0的節點
		point.resize(nodeNum); //陣列大小跟隨graph
		for (int x, y; nodeNum--;) //輸入測資並建無向圖
		{
			cin >> y >> buf >> x >> buf;
			while (x--)
			{
				graph[y].push_back(int()); //每次先在最後增加一格
				cin >> graph[y].back(); //再將資料輸入該格中，而因測資會給所有點的連接狀況，故只需建單向即可，最後建完的就會是雙向圖
			}
		}

		for (int time, y = 0; y < graph.size(); y++) //跑dfs，所有點檢查一次
		{
			if (point[y].order == 0) //若該點的order == 0
			{
				dfs_find_bridge(y, y, time = 1); //代表該點還沒有走過，以此為root跑dfs找bridge
			}
		}

		for (cout << output.size() << " critical links\n"; output.size(); output.pop()) //將所有結果輸出(頂端為最小)
		{
			cout << output.top().first << " - " << output.top().second << endl;
		}
	}

	system("pause");
}