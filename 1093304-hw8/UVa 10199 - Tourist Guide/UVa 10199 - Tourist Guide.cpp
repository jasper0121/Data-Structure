#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

struct node { int order = 0, low = 0; }; //每個節點紀錄順序，及一個可追朔到最遠並形成環的祖先
vector<vector<int>>graph; //無向圖
vector<node>point; //記錄每一點的狀態
map<string, const int>placeName; //存地名和給一個對應編號
set<string>output; //所有被當成cut point的地名

void dfs_find_cut_point(int cur, int par, int& time) //current、parent
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
					cutPoint = true;
				}
			}
		}
	}

	if (cutPoint) //若為割點
	{
		for (auto it = placeName.begin(); it != placeName.end(); it++) //將割點轉回相對應的字串
		{
			if (cur == it->second)
			{
				output.insert(it->first); //題目要求字串輸出照順序，故將其存入set中排序
				break;
			}
		}
	}
}

int main()
{
	string inputName; //輸入地名
	for (int placeNum, roadNum, testCase = 1; cin >> placeNum, placeNum; graph.clear(), point.clear(), placeName.clear(), output.clear())
	{
		graph.resize(placeNum);
		point.resize(placeNum);
		for (int n = 0; n < placeNum; n++) //輸入地名並給予對應的編號存入map
		{
			cin >> inputName;
			placeName.insert({ inputName,n });
		}

		cin >> roadNum; //輸入道路數
		for (string start, end; roadNum--;) //輸入測資並建無向圖(將地名轉成對應的編號)
		{
			cin >> start >> end;
			graph[placeName[start]].push_back(placeName[end]);
			graph[placeName[end]].push_back(placeName[start]);
		}

		for (int time, y = 0; y < graph.size(); y++) //跑dfs，所有點檢查一次
		{
			if (point[y].order == 0) //若該點的order == 0
			{
				dfs_find_cut_point(y, y, time = 1); //代表該點還沒有走過，以此為root跑dfs找cut point
			}
		}

		if (testCase != 1) //除第1筆測資外，每筆測資輸出前先空一行
		{
			cout << endl;
		}

		cout << "City map #" << testCase++ << ": " << output.size() << " camera(s) found\n";
		for (auto it = output.begin(); it != output.end(); cout << *it++ << endl); //輸出作為割點的地名(輸出順序由A ~ Z由短到長)
	}

	system("pause");
}