#include<iostream>
#include<queue>
#include<map>
using namespace std;

struct car
{
	int num = 0, distance = 0; //車子的輸入順序、車子離河岸的距離(開到河岸所花費的時間)
}input;

int main()
{
	int testCase, shipCapacity, shipSpendTime, carNum, shipTotalTime = 0; //測資數、船的容量、船渡河的時間、車的總數、船的總花費時間
	string side; //河岸、輸入left或right
	multimap<int, int>output; //key == 車子的輸入順序、value == 車子從一開始到渡河所花費的時間
	for (cin >> testCase; testCase--; shipTotalTime = 0, output.clear())
	{
		queue<car>carQueue[2]; //河的兩岸等待的車隊，0 == 左岸、1 == 右岸
		cin >> shipCapacity >> shipSpendTime >> carNum; //船的容量、船渡河的時間、車的總數
		for (int i = 0; i < carNum; i++)
		{
			input.num = i; //後面會將順序打亂，而題目要求輸出順序和輸入要相同，故紀錄輸入順序
			cin >> input.distance >> side; //輸入離河岸的距離和在河的哪一岸
			side == "left" ? carQueue[0].push(input) : carQueue[1].push(input); //根據車的位置將數據放入相對應的queue
		}

		for (int i = 0; carQueue[0].size() || carQueue[1].size(); ++i %= 2) //i == 船當前所在岸，若至少有一岸還有車
		{
			if (carQueue[i].size() && carQueue[(i + 1) % 2].size()) //若兩岸都有車
			{
				if (shipTotalTime < min(carQueue[i].front().distance, carQueue[(i + 1) % 2].front().distance)) //若船的總花費時間 < 距離河岸較短的車
				{
					shipTotalTime = min(carQueue[i].front().distance, carQueue[(i + 1) % 2].front().distance); //則距離較小的一方當作船的總花費時間
				}
			}
			else //若有其中一岸沒有車
			{
				if (carQueue[i].size()) //若船當前所在的河岸有車(對岸無車)
				{
					if (carQueue[i].front().distance > shipTotalTime) //若車子到岸距離較大
					{
						shipTotalTime = carQueue[i].front().distance; //則將該距離當作船的總花費時間(相當於船等車子到岸)
					}
				}
				else //若船當前所在的河岸無車(對岸有車)
				{
					if (carQueue[(i + 1) % 2].front().distance > shipTotalTime) //若車子到岸距離較大
					{
						shipTotalTime = carQueue[(i + 1) % 2].front().distance; //則將該距離當作船的總花費時間(相當於船等車子到岸)
					}
				}
			}

			//渡河。若船還有空間且當前河岸還有車隊且已有車到岸邊
			for (int c = shipCapacity; c-- && carQueue[i].size() && shipTotalTime >= carQueue[i].front().distance;)
			{
				output.insert({ carQueue[i].front().num,shipTotalTime + shipSpendTime }); //將該車的資料加入multimap中，渡河還要加上shipSpendTime
				carQueue[i].pop(); //車已渡河，從車隊中刪除
			}

			shipTotalTime += shipSpendTime; //渡河後將渡河的時間加入總花費時間
		}

		for (auto it = output.begin(); it != output.end(); it++) //auto == multimap<int, int>::iterator
		{
			cout << it->second << endl; //印出所有車渡河過程所花費的時間
		}

		if (testCase) //最後的testCase不要換行
		{
			cout << endl;
		}
	}

	system("pause");
}