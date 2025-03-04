#include<iostream>
#include<vector>
using namespace std;

struct node { int order = 0, low = 0; }; //每個節點紀錄順序，及一個可追朔到最遠並形成環的祖先
vector<vector<int>>graph; //無向圖
vector<node>point; //記錄每一點的狀態
vector<int>bridge; //記錄橋，在index(current)裡存parent

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
		bridge[par] = bridge[cur] = par; //cur和par間的連結為橋，output中的cur和par位置都紀錄par，作為之後要做並查集使用(par是自己的parent)
	}
}

int find_root(int child) //並查集，找child的根
{
	return bridge[child] == child ? child : find_root(bridge[child]); //若child的值和index同，代表child是root；否則繼續向上找
}

int main()
{
	//房間數、走廊數、查詢次數；每次資料重置
	for (int room, corridor, query; cin >> room >> corridor >> query, room; cout << "-\n", graph.clear(), point.clear(), bridge.clear())
	{
		graph.resize(room + 1); //題目的節點編號最小為1，故0不用
		point.resize(room + 1); //陣列大小跟隨graph
		bridge.resize(room + 1); //使節點編號有相對應index，故0不用
		for (int x, y; corridor--;) //輸入測資並建無向圖
		{
			cin >> y >> x;
			graph[y].push_back(x);
			graph[x].push_back(y);
		}

		for (int time, y = 1; y < graph.size(); y++) //跑dfs，所有點檢查一次
		{
			if (point[y].order == 0) //若該點的order == 0
			{
				dfs_find_bridge(y, y, time = 1); //代表該點還沒有走過，以此為root跑dfs找bridge
			}
		}

		for (int start, end, startRoot, endRoot; query--;) //題求從start到end能否只藉由走橋來到達，查詢query次
		{
			cin >> start >> end;
			//起點和終點分別向上走橋找自己的root，若root相同，代表可以從start走到end
			cout << ((startRoot = find_root(start)) && (endRoot = find_root(end)) && startRoot == endRoot ? "Y\n" : "N\n");
		}
	}

	system("pause");
}