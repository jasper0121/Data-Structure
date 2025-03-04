#include<iostream>
#include<vector>
using namespace std;

vector<string>graph; //�إߦa��

void dfs(int x, int y)
{
	if (y < graph.size() && x < graph[y].size())
	{
		if (graph[y][x] == 'x' || graph[y][x] == '@') //'@' == ��Q���I���@�����A�G�bdfs�ɥi�����N'@'��'x'
		{
			graph[y][x] = ' '; //�C���N���I�]���ť�
			dfs(x - 1, y); //��
			dfs(x, y - 1); //�W
			dfs(x + 1, y); //�k
			dfs(x, y + 1); //�U
		}
	}
}

int main()
{
	int testCase, shipNum = 0; //����ơB��Ӽ�
	cin >> testCase;
	for (int n, t = 1; t <= testCase; t++, graph.clear(), shipNum = 0) //n == ���e�B�C����l��
	{
		cin >> n;
		graph.resize(n); //�إ߰}�C�j�p
		for (int y = 0; y < graph.size(); cin >> graph[y++]); //��J�a�Ϧr��
		for (int x = 0, y = 0; y < graph.size(); x = 0, y++)
		{
			for (; (x = graph[y].find('x', x)) != -1; dfs(x++, y), shipNum++); //�Y�b��e�r�ꤤ����@����('x')�h�]dfs�A����qx + 1���a���~���A��� + 1
		}

		cout << "Case " << t << ": " << shipNum << endl;
	}

	system("pause");
}