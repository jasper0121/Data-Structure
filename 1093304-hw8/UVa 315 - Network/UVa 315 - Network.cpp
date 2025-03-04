#include<iostream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

struct node { int order = 0, low = 0; }; //每個節點紀錄順序，及一個可追朔到最遠並形成環的祖先
vector<vector<int>>graph; //無向圖
vector<node>point; //記錄每一點的狀態
int cutPointNum = 0; //割點數量(若拿掉割點，則圖會分離成2個以上)

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
				point[cur].low = min(point[cur].low, point[graph[cur][x]].low); //若當前的點low值較大，則將其改為child的low值

				//若當前的點非根且連接的其中一個子代，其low >=cur的節點編號，代表該子代的子樹中沒有任何一點連到cur之前，此時若將cur拿掉則會使圖分離
				//若當前的點為根，前面以根的狀態跑dfs證明根有child，故child數先 + 1，若child >= 2則代表根為割點
				if ((cur != par && point[cur].order <= point[graph[cur][x]].low) || (cur == par && ++rootChildNum == 2))
				{
					cutPoint = true;
				}
			}
		}
	}

	if (cutPoint) //若為割點
	{
		cutPointNum++; //則割點數 + 1
	}
}

int main()
{
	string input; //輸入測資
	stringstream string_to_int; //將字串中的數字轉成int，每次以空格為讀取分界點
	for (int nodeNum; cin >> nodeNum, nodeNum; graph.clear(), point.clear(), cutPointNum = 0) //輸入點個數，每次資料重置
	{
		graph.resize(nodeNum + 1); //題目的節點編號最小為1，故0不用
		point.resize(nodeNum + 1); //陣列大小跟隨graph
		for (int start, end; cin >> start, start; string_to_int.clear()) //因題目輸入和start連接的end數不固定，且每個數字間以空格隔開，故使用stringstream
		{
			cin.ignore(); //在前面確定start不為0後，因之後要和getline混用，故先清除cin的暫存區以避免輸入錯誤
			getline(cin, input); //將之後的數個end先以字串方式輸入
			for (string_to_int << input; !string_to_int.eof();) //將input放入stringstream轉換成int；在讀到字串結尾之前
			{
				string_to_int >> end; //每次將空格前的數轉成int給end
				graph[start].push_back(end); //建無向圖
				graph[end].push_back(start);
			}
		}

		for (int time, y = 1; y < graph.size(); y++) //跑dfs，所有點檢查一次
		{
			if (point[y].order == 0) //若該點的order == 0
			{
				dfs_find_cut_point(y, y, time = 1); //代表該點還沒有走過，以此為root跑dfs找cut point
			}
		}

		cout << cutPointNum << endl; //題求割點數
	}

	system("pause");
}