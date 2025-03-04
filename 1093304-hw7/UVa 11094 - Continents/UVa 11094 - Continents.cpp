#include<iostream>
#include<vector>
using namespace std;

vector<string>graph; //�إߦa��
char land; //�O����eking�Ҧb����m(���w�O���a)

void dfs(int x, int y, int& counter)
{
	if (y < graph.size())
	{
		if (graph[y][x] == land) //�Y��e���I == land
		{
			graph[y][x] = ' '; //�N���I�]���ť�
			counter++;
			dfs((x ? x - 1 : graph[y].size() - 1), y, counter); //��(���k�s�q)
			dfs(x, y - 1, counter); //�W
			dfs((x == graph[y].size() - 1 ? 0 : x + 1), y, counter); //�k(���k�s�q)
			dfs(x, y + 1, counter); //�U
		}
	}
}

int main()
{
	int pos_X, pos_Y, counter = 0, maxLand = 0; //king���y�СB�������a���n�B�̤j���a���n
	for (int row, col; cin >> row >> col; graph.clear(), maxLand = 0) //��J�e�M���F�C����l��
	{
		graph.resize(row); //�]�w�}�C�j�p(�C�� == �e��)
		for (int y = 0; y < row; cin >> graph[y++]); //��J�a��
		cin >> pos_Y >> pos_X; //��Jking�Ҧb����m
		land = graph[pos_Y][pos_X]; //�Nking�Ҧb���r���������a
		dfs(pos_X, pos_Y, counter); //�D�بD��king�Ҧb�H�~���̤j���a�A�G��dfs��king�Ҧb�����a�R���A�H�K���᪺dfs�v�T�P�_
		for (int x = 0, y = 0; y < graph.size(); x = 0, y++)
		{
			while ((x = graph[y].find(land, x)) != -1) //�q�C�Ӧr��}�l��A�Y�b��e�r�ꤤ���land
			{
				dfs(x++, y, counter = 0); //�h����counter = 0�A�A�]dfs���land���j�p�Adfs��qx + 1����m�~���U�@��land
				maxLand = max(counter, maxLand); //�Ycounter���j�A�hmaxLand = counter
			}
		}

		cout << maxLand << endl;
	}

	system("pause");
}