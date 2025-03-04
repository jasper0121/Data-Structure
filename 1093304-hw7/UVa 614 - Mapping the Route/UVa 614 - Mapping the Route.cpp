#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

vector<vector<int>>maze, path; //�إ߰g�c�ϡB���|
bool work = true; //�g�c�樫���A�A�Y�w���X�g�c�h�]��false

void dfs(int start_X, int start_Y, const int& end_X, const int& end_Y, int order) //�P�_���ǥ��W�k�U
{
	path[start_Y][start_X] = order; //�C�����b�Ӯ�����樫����

	if (start_X == end_X && start_Y == end_Y) //�Y������I
	{
		work = false; //���A�]��false�N��w����
		return;
	}

	//���A�Ystart_X - 1 == 0�N��I�쥪�~��B!path[start_Y][start_X - 1] == ���䪺���|�٨S���L(�Y���L�h�@�w�|�d�U-1�Τj��0������)(�H�U�P�z)
	if (work && start_X - 1 && maze[start_Y][start_X - 1] != 1 && maze[start_Y][start_X - 1] != 3 && !path[start_Y][start_X - 1])
	{
		dfs(start_X - 1, start_Y, end_X, end_Y, order + 1);
	}

	//�W�A�Ystart_Y - 1 == 0�N��I��W�~��
	if (work && start_Y - 1 && maze[start_Y - 1][start_X] != 2 && maze[start_Y - 1][start_X] != 3 && !path[start_Y - 1][start_X])
	{
		dfs(start_X, start_Y - 1, end_X, end_Y, order + 1);
	}

	//�k�A�Ystart_X + 1 == maze[start_Y].size()�N��I��k�~��
	if (work && start_X + 1 != maze[start_Y].size() && maze[start_Y][start_X] != 1 && maze[start_Y][start_X] != 3 && !path[start_Y][start_X + 1])
	{
		dfs(start_X + 1, start_Y, end_X, end_Y, order + 1);
	}

	//�U�A�Ystart_Y + 1 == maze.size()�N��I��U�~��
	if (work && start_Y + 1 != maze.size() && maze[start_Y][start_X] != 2 && maze[start_Y][start_X] != 3 && !path[start_Y + 1][start_X])
	{
		dfs(start_X, start_Y + 1, end_X, end_Y, order + 1);
	}

	if (work) //�Y����Ĳ�o�A�N��I�즺���A��e�Ӯ�令-1
	{
		path[start_Y][start_X] = -1;
	}
}

int main()
{
	int height, width, start_X, start_Y, end_X, end_Y; //�g�c�����שM�e�סB�_�Ixy�y�СB���Ixy�y��
	//num == �ĴX�Ӱg�c�F�C����J���e�B�_�I�B���I�A��J�h���X�F�C����l��
	for (int num = 1; cin >> height >> width >> start_Y >> start_X >> end_Y >> end_X, height; maze.clear(), path.clear(), num++, work = true)
	{
		maze.resize(height + 1, vector<int>(width + 1)); //�]�w�g�c����(0����)�A�C�椺�]�w�e��(0����)
		path = maze; //���|�t�m�M�g�c�ۦP
		for (int y = 1; y < maze.size(); y++) //��J�g�c���C�檺��t�m�A0 == �L��B1 == �F��B2 == �n��B3 == ����
		{
			for (int x = 1; x < maze[y].size(); cin >> maze[y][x++]);
		}

		dfs(start_X, start_Y, end_X, end_Y, 1); //���g�c�A�樫���Ǳq1�}�l

		cout << "Maze " << num << endl << endl; //�}�l�e��
		for (int c = width; cout << "+", c--; cout << "---"); //�W��~��
		cout << endl;

		for (int y = 1; y <= height; y++) //�e���k�~��B�����𵲺c�B�g�c�樫����
		{
			cout << "|";
			for (int x = 1; x <= width; x++)
			{
				if (path[y][x] == -1) //-1�N��Ӹ��|���L���I�즺���A��X???
				{
					cout << "???";
				}
				else if (path[y][x]) //�L�X�Ӯ檺�樫����
				{
					cout << setw(3) << path[y][x]; //setw(3) == �w�d3��A�ϫ᭱����X�a�k��ܡA�e�����ϥΪ������h��J�Ů�
				}
				else //0�A�N��S�����L�Ӯ�
				{
					cout << "   ";
				}

				cout << (maze[y][x] == 1 || maze[y][x] == 3 || x == width ? "|" : " "); //�e�F��(�Y�I��~��h�@�w�n�e)
			}

			cout << endl;
			if (y != height)
			{
				for (int x = 1; cout << "+", x <= width; cout << (maze[y][x] == 2 || maze[y][x] == 3 ? "---" : "   "), x++); //�e�n��(���]�A�̩��~��)
				cout << endl;
			}
		}

		for (int c = width; cout << "+", c--; cout << "---"); //�U��~��
		cout << endl << endl << endl;
	}

	system("pause");
}