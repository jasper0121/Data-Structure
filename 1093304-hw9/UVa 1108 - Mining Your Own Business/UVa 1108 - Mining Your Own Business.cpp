#include<iostream>
#include<vector>
#include<set>
using namespace std;

struct node { int order = 0, low = 0; }; //順序、可追朔的最小點
vector<vector<int>>graph; //無向圖
vector<node>point; //記錄每一點的狀態
vector<bool>cutPoint; //記錄每個點是不是cut point
vector<set<int>>component;
vector<pair<int, int>>inStack; //用vector模擬stack來暫存在dfs時所經過的點

void dfs_biconnected_component(int cur, int par, int& time) //點雙連通分量
{
	int rootChildNum = 0; //根所連接的child(不包括以back edge連接的節點)
	point[cur].order = point[cur].low = time++; //每次先做順序記號代表已走過
	for (int x = 0; x < graph[cur].size(); x++) //檢查和當前連接的所有點
	{
		if (graph[cur][x] != par) //若接下來要走訪的點不是parent
		{
			if (point[graph[cur][x]].order) //如果下一個要走訪的order不是0，代表下一個點已走訪過
			{
				point[cur].low = min(point[cur].low, point[graph[cur][x]].order); //若下一個要走訪的節點編號較小，則將其值給當前的low
			}
			else
			{
				rootChildNum++;
				inStack.push_back({ cur, graph[cur][x] }); //在進行dfs前先將當前的edge存起來
				dfs_biconnected_component(graph[cur][x], cur, time); //下一個點還沒走訪過，繼續跑dfs
				point[cur].low = min(point[cur].low, point[graph[cur][x]].low); //若當前的點low值較大，則將其改成child的low值
				//若當前的點連接的其中一個子代，其low >=cur的節點編號，代表該子代的子樹中沒有任何一點連到cur之前，此時若將cur拿掉則會使圖分離
				if (point[cur].order <=point[graph[cur][x]].low )
				{
					cutPoint[cur] = true; //代表當前的點是cut point
					component.push_back(set<int>()); //增加1格以存component的各種節點
					pair<int, int>temp; //暫存
					do
					{
						temp = inStack.back(); //每次紀錄stack的top
						inStack.pop_back(); //stack先pop
						component.back().insert(temp.first); //存入2點
						component.back().insert(temp.second);
					} while (temp != pair<int, int>(cur, graph[cur][x])); //一直pop到最後出來的是當前的邊，過程中所pop出來的元素皆為同個component
				}
			}
		}
	}

	if (cur == par && rootChildNum < 2) //最後檢查，若根的child < 2代表根非cut point
	{
		cutPoint[cur] = false;
	}
}

int main()
{
	for (int tunnel, time, testCase = 1; cin >> tunnel, tunnel; component.clear()) //隧道數，每次將component內資料清空
	{
		graph.assign(tunnel + 2, vector<int>()); //0不用，且節點數 == 隧道數 + 1(一條線可產生頭尾2點)，故陣列空間數 == tunnel + 2
		point.assign(tunnel + 2, node()); //0不用，且節點數 == 隧道數 + 1
		cutPoint.assign(tunnel + 2, false); //0不用，且節點數 == 隧道數 + 1
		for (int x, y; tunnel--;) //建無向圖
		{
			cin >> y >> x;
			graph[y].push_back(x);
			graph[x].push_back(y);
		}

		dfs_biconnected_component(1, 1, time = 1); //所有節點互相連接，故以節點1開始跑dfs即可
		if (component.size() == 1) //若component只有1個
		{
			//代表無cut point，最少須設置2點，且方法數為C的n取2，化簡後 == n (n - 1) / 2
			cout << "Case " << testCase++ << ": " << 2 << " " << component[0].size() * (component[0].size() - 1) / 2 << endl; //輸出題目要求
			continue;
		}

		long long int minChoice = 0, total = 1; //反之若有2個以上component，設最小選擇的點個數、總方法數
		for (int i = 0; i < component.size(); i++)
		{
			int cpNum = 0; //當前component中的cut point數量
			for (auto it = component[i].begin(); it != component[i].end(); it++) //對所有的component
			{
				if (cutPoint[*it]) //若當前指向的點是cut point
				{
					cpNum++; //則cut point數量 + 1
				}
			}

			if (cpNum == 1) //若當前的component只有1個cut point
			{
				minChoice++; //則要在該component中選擇一點
				total *= component[i].size() - 1; //將當前除cut point的其他點乘起來
			}
		}

		cout << "Case " << testCase++ << ": " << minChoice << " " << total << endl; //輸出題目要求
	}

	system("pause");
}