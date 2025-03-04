#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct node { int order = 0, low = 0; }; //每個節點紀錄順序，及一個可追朔到最遠並形成環的祖先
vector<vector<int>>graph; //無向圖
vector<node>point; //記錄每一點的狀態
vector<pair<int, int>>output; //紀錄拆掉cut point後所分離的圖個數，first == 點的編號、second == 分離的圖個數；初始first == index，之後排序會打亂

bool comp(const pair<int, int>& left, const pair<int, int>& right) //題求將分離的圖數(second)由大到小排序，若相同則以點編號(first)由小到大排序
{
	return left.second == right.second ? left.first<right.first : left.second>right.second;
}

void dfs_find_cut_point(int cur, int par, int& time) //current、parent、順序記號
{
	bool cutPoint = false; //當前的點是否為割點
	int rootChildNum = 0; //root的child數(不包括以back edge連回來的點)，若等於2則root為割點
	point[cur].order = point[cur].low = time++; //每次先做順序記號代表已走過
	for (int x = 0; x < graph[cur].size(); x++) //檢查和當前連接的所有點
	{
		if (graph[cur][x] != par) //若接下來要走訪的點不是parent(若此if不檢查、則會把cur和par間的連結當成back edge而導致錯誤)
		{
			if (point[graph[cur][x]].order) //如果下一個要走訪的order不是0，代表下一個點已走訪過
			{
				point[cur].low = min(point[cur].low, point[graph[cur][x]].order); //若下一個要走訪的節點編號較小，則將其值給當前的low
			}
			else
			{
				dfs_find_cut_point(graph[cur][x], cur, time); //反之代表下一個點還沒走訪過，繼續跑dfs
				point[cur].low = min(point[cur].low, point[graph[cur][x]].low); //若當前的點low值較大，則將其改成child的low值

				//若當前的點非根且連接的其中一個子代，其low >=cur的節點編號，代表該子代的子樹中沒有任何一點連到cur之前，此時若將cur拿掉則會使圖分離
				//若當前的點為根，前面以根的狀態跑dfs證明根有child，故child數先 + 1，若child >= 2則代表根為割點
				if ((cur != par && point[cur].order <= point[graph[cur][x]].low) || (cur == par && ++rootChildNum == 2))
				{
					output[cur].second++; //每次條件成立，代表對下個點而言cur是割點，最後output[cur].second == 拆掉cut point後所分離的無向圖數
				}
			}
		}
	}
}

int main()
{
	for (int station, target; cin >> station >> target, station; cout << endl, graph.clear(), point.clear(), output.clear()) //target == 輸出次數
	{
		graph.resize(station);
		point.resize(station);
		for (int i = 0; i < station; output.push_back({ i++ , 1 })); //output大小 == station數，任何點拆掉後至少會產生1個無向圖
		for (int x, y; cin >> y >> x, y != -1;) //輸入測資並建無向圖，若輸入-1則跳出
		{
			graph[y].push_back(x);
			graph[x].push_back(y);
		}

		for (int time, y = 0; y < graph.size(); y++) //跑dfs，所有點檢查一次
		{
			if (point[y].order == 0) //若該點的order == 0
			{
				dfs_find_cut_point(y, y, time = 1); //代表該點還沒有走過，以此為root跑dfs找cut point
			}
		}

		sort(output.begin(), output.end(), comp); //根據題目所求將output排序
		for (int i = 0; i < target; i++) //印出前target數的答案
		{
			cout << output[i].first << " " << output[i].second << endl;
		}
	}

	system("pause");
}