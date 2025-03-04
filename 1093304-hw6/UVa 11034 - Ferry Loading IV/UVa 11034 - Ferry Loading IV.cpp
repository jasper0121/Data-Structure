#include<iostream>
#include<queue>
using namespace std;

int main()
{
	int testCase, shipLength, carNum, carLength, counter = 0; //測資數、船的長度(公尺)、車的總數、車的長度(公分)、船的渡河次數
	string side; //河岸、輸入left或right
	for (cin >> testCase; testCase--; counter = 0) //每次渡河次數重置
	{
		queue<int>carQueue[2]; //河的兩岸等待的車隊，0 == 左岸、1 == 右岸
		cin >> shipLength >> carNum; //輸入船的長度和車子總數
		shipLength *= 100; //公尺轉公分
		for (int n = carNum; n--;)
		{
			cin >> carLength >> side; //輸入車子長度和在河的左或右岸
			side == "left" ? carQueue[0].push(carLength) : carQueue[1].push(carLength); //根據車的位置將數據放入相對應的queue
		}

		for (int i = 0; carQueue[0].size() || carQueue[1].size(); ++i %= 2, counter++) //若至少有一岸還有車，每次船的渡河次數 + 1
		{
			for (int capacity = shipLength; carQueue[i].size() && capacity >= carQueue[i].front();) //若該岸還有車隊存在且若船還容納得下當前的車
			{
				capacity -= carQueue[i].front(); //當前的車放入船中，故船的空間減少
				carQueue[i].pop(); //該車從車隊中刪除
			}
		}

		cout << counter << endl; //輸出船的渡河次數
	}

	system("pause");
}