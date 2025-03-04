#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

vector<vector<int>>maze, path; //建立迷宮圖、路徑
bool work = true; //迷宮行走狀態，若已走出迷宮則設為false

void dfs(int start_X, int start_Y, const int& end_X, const int& end_Y, int order) //判斷順序左上右下
{
	path[start_Y][start_X] = order; //每次先在該格紀錄行走順序

	if (start_X == end_X && start_Y == end_Y) //若走到終點
	{
		work = false; //狀態設為false代表已走完
		return;
	}

	//左，若start_X - 1 == 0代表碰到左外牆、!path[start_Y][start_X - 1] == 左邊的路徑還沒走過(若走過則一定會留下-1或大於0的紀錄)(以下同理)
	if (work && start_X - 1 && maze[start_Y][start_X - 1] != 1 && maze[start_Y][start_X - 1] != 3 && !path[start_Y][start_X - 1])
	{
		dfs(start_X - 1, start_Y, end_X, end_Y, order + 1);
	}

	//上，若start_Y - 1 == 0代表碰到上外牆
	if (work && start_Y - 1 && maze[start_Y - 1][start_X] != 2 && maze[start_Y - 1][start_X] != 3 && !path[start_Y - 1][start_X])
	{
		dfs(start_X, start_Y - 1, end_X, end_Y, order + 1);
	}

	//右，若start_X + 1 == maze[start_Y].size()代表碰到右外牆
	if (work && start_X + 1 != maze[start_Y].size() && maze[start_Y][start_X] != 1 && maze[start_Y][start_X] != 3 && !path[start_Y][start_X + 1])
	{
		dfs(start_X + 1, start_Y, end_X, end_Y, order + 1);
	}

	//下，若start_Y + 1 == maze.size()代表碰到下外牆
	if (work && start_Y + 1 != maze.size() && maze[start_Y][start_X] != 2 && maze[start_Y][start_X] != 3 && !path[start_Y + 1][start_X])
	{
		dfs(start_X, start_Y + 1, end_X, end_Y, order + 1);
	}

	if (work) //若條件觸發，代表碰到死路，當前該格改成-1
	{
		path[start_Y][start_X] = -1;
	}
}

int main()
{
	int height, width, start_X, start_Y, end_X, end_Y; //迷宮的高度和寬度、起點xy座標、終點xy座標
	//num == 第幾個迷宮；每次輸入高寬、起點、終點，輸入則跳出；每次初始化
	for (int num = 1; cin >> height >> width >> start_Y >> start_X >> end_Y >> end_X, height; maze.clear(), path.clear(), num++, work = true)
	{
		maze.resize(height + 1, vector<int>(width + 1)); //設定迷宮高度(0不用)，每格內設定寬度(0不用)
		path = maze; //路徑配置和迷宮相同
		for (int y = 1; y < maze.size(); y++) //輸入迷宮內每格的牆配置，0 == 無牆、1 == 東牆、2 == 南牆、3 == 都有
		{
			for (int x = 1; x < maze[y].size(); cin >> maze[y][x++]);
		}

		dfs(start_X, start_Y, end_X, end_Y, 1); //走迷宮，行走順序從1開始

		cout << "Maze " << num << endl << endl; //開始畫圖
		for (int c = width; cout << "+", c--; cout << "---"); //上方外牆
		cout << endl;

		for (int y = 1; y <= height; y++) //畫左右外牆、內部牆結構、迷宮行走紀錄
		{
			cout << "|";
			for (int x = 1; x <= width; x++)
			{
				if (path[y][x] == -1) //-1代表該路徑走過但碰到死路，輸出???
				{
					cout << "???";
				}
				else if (path[y][x]) //印出該格的行走順序
				{
					cout << setw(3) << path[y][x]; //setw(3) == 預留3格，使後面的輸出靠右表示，前面未使用的部分則填入空格
				}
				else //0，代表沒有走過該格
				{
					cout << "   ";
				}

				cout << (maze[y][x] == 1 || maze[y][x] == 3 || x == width ? "|" : " "); //畫東牆(若碰到外牆則一定要畫)
			}

			cout << endl;
			if (y != height)
			{
				for (int x = 1; cout << "+", x <= width; cout << (maze[y][x] == 2 || maze[y][x] == 3 ? "---" : "   "), x++); //畫南牆(不包括最底外牆)
				cout << endl;
			}
		}

		for (int c = width; cout << "+", c--; cout << "---"); //下方外牆
		cout << endl << endl << endl;
	}

	system("pause");
}