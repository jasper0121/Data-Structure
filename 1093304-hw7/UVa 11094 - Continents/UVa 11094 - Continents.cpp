#include<iostream>
#include<vector>
using namespace std;

vector<string>graph; //建立地圖
char land; //記錄當前king所在的位置(必定是陸地)

void dfs(int x, int y, int& counter)
{
	if (y < graph.size())
	{
		if (graph[y][x] == land) //若當前的點 == land
		{
			graph[y][x] = ' '; //將該點設為空白
			counter++;
			dfs((x ? x - 1 : graph[y].size() - 1), y, counter); //左(左右連通)
			dfs(x, y - 1, counter); //上
			dfs((x == graph[y].size() - 1 ? 0 : x + 1), y, counter); //右(左右連通)
			dfs(x, y + 1, counter); //下
		}
	}
}

int main()
{
	int pos_X, pos_Y, counter = 0, maxLand = 0; //king的座標、紀錄陸地面積、最大陸地面積
	for (int row, col; cin >> row >> col; graph.clear(), maxLand = 0) //輸入寬和長；每次初始化
	{
		graph.resize(row); //設定陣列大小(列數 == 寬度)
		for (int y = 0; y < row; cin >> graph[y++]); //輸入地圖
		cin >> pos_Y >> pos_X; //輸入king所在的位置
		land = graph[pos_Y][pos_X]; //將king所在的字元視為陸地
		dfs(pos_X, pos_Y, counter); //題目求除king所在以外的最大陸地，故先dfs把king所在的陸地刪掉，以免之後的dfs影響判斷
		for (int x = 0, y = 0; y < graph.size(); x = 0, y++)
		{
			while ((x = graph[y].find(land, x)) != -1) //從每個字串開始找，若在當前字串中找到land
			{
				dfs(x++, y, counter = 0); //則先使counter = 0，再跑dfs算該land的大小，dfs後從x + 1的位置繼續找下一個land
				maxLand = max(counter, maxLand); //若counter較大，則maxLand = counter
			}
		}

		cout << maxLand << endl;
	}

	system("pause");
}