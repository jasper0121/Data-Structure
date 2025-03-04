#include<iostream>
#include<vector>
using namespace std;

vector<string>graph; //建立地圖

void dfs(int x, int y)
{
	if (y < graph.size() && x < graph[y].size())
	{
		if (graph[y][x] == 'x' || graph[y][x] == '@') //'@' == 船被擊沉的一部份，故在dfs時可直接將'@'當成'x'
		{
			graph[y][x] = ' '; //每次將該點設為空白
			dfs(x - 1, y); //左
			dfs(x, y - 1); //上
			dfs(x + 1, y); //右
			dfs(x, y + 1); //下
		}
	}
}

int main()
{
	int testCase, shipNum = 0; //測資數、船個數
	cin >> testCase;
	for (int n, t = 1; t <= testCase; t++, graph.clear(), shipNum = 0) //n == 長寬、每次初始化
	{
		cin >> n;
		graph.resize(n); //建立陣列大小
		for (int y = 0; y < graph.size(); cin >> graph[y++]); //輸入地圖字串
		for (int x = 0, y = 0; y < graph.size(); x = 0, y++)
		{
			for (; (x = graph[y].find('x', x)) != -1; dfs(x++, y), shipNum++); //若在當前字串中找到船的一部份('x')則跑dfs，之後從x + 1的地方繼續找，船數 + 1
		}

		cout << "Case " << t << ": " << shipNum << endl;
	}

	system("pause");
}