#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>>graph; //建立有向圖
vector<bool>node; //紀錄所有點的經過與否狀態

void dfs(int startPos, int& counter)
{
	for (int i = 0; i < graph[startPos].size(); i++) //每個點都可能會有複數個分支連向其他點(單向)，每次將該點的所有分支都試圖走過一遍
	{
		if (node[graph[startPos][i]] == false) //若該點所連的下一個點還未走訪過
		{
			node[graph[startPos][i]] = true; //則接下來將走訪該點，將該點狀態設為true
			dfs(graph[startPos][i], --counter); //未經過的點個數先 - 1，再往該點繼續走訪
		}
	}
}

int main()
{
	vector<int>start; //存所有要進行dfs的起始點
	for (int nodeNum, startNum; cin >> nodeNum, nodeNum; graph.clear(), start.clear()) //節點個數、每次要dfs的起始個數；輸入則跳出；每次初始化
	{
		graph.resize(nodeNum + 1); //設定陣列大小，0不用
		for (int y; cin >> y, y;) //每次輸入起始點，輸入0則跳出
		{
			for (int x; cin >> x, x; graph[y].push_back(x)); //每次輸入終點存入y底下，代表y → x
		}

		cin >> startNum; //輸入要跑dfs時的起點數
		start.resize(startNum); //根據起點數設定陣列大小
		for (int i = 0; i < startNum; cin >> start[i++]); //輸入所有起點

		//每次先node重置(0不用且所有初始狀態為false)、counter == 紀錄未經過的點個數，在所有起始點還沒測過之前
		for (int counter, i = 0; node.resize(nodeNum + 1), i < startNum; i++, node.clear(), cout << endl)
		{
			dfs(start[i], counter = nodeNum); //跑dfs(每次counter初始為點個數)，目的求出每次從start[i]開始走後，最終無法走訪到的點個數
			cout << counter; //輸出無法走訪到的點個數
			for (int i = 1; i < node.size(); i++) //再將那些點一一印出來
			{
				if (node[i] == false)
				{
					cout << " " << i;
				}
			}
		}
	}

	system("pause");
}