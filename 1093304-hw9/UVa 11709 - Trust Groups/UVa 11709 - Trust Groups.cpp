#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

struct node { int order = 0, low = 0; }; //順序、可追朔的最小點
vector<vector<int>>graph; //有向圖
vector<node>point; //記錄每一點的狀態
vector<int>inStack; //用vector模擬stack來暫存在dfs時所經過的點
map<string, int>name; //將字串轉成對應數字
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
		//一直pop到最後pop出來的是cut point，過程中所pop出來的元素皆為同個component
		for (int temp; temp = inStack.back(), inStack.pop_back(), temp != cur;); //暫存，每次紀錄stack的top、stack先pop
		cpnNum++;
	}
}

int main()
{
	string input; //輸入名字
	for (int people, link; cin >> people >> link, people; name.clear(), cpnNum = 0) //點、邊；每次初始化
	{
		cin.ignore(); //cin將和getline混用，先將cin的暫存區清除
		graph.assign(people, vector<int>()); //建立陣列大小(assign包含clear)
		point.assign(people, node()); //建立陣列大小(assign包含clear)
		for (int n = 0; people--; n++) //輸入所有名字並將其編號
		{
			getline(cin, input);
			name.insert({ input ,n });
		}

		for (string start, end; link--;) //建有向圖
		{
			getline(cin, start);
			getline(cin, end);
			graph[name[start]].push_back(name[end]);
		}

		for (int time, y = 0; y < graph.size(); y++) //找形成環的component
		{
			if (point[y].order == 0)
			{
				dfs_strong_connect_component(y, time = 1);
			}
		}

		cout << cpnNum << endl; //答案求component數
	}

	system("pause");
}