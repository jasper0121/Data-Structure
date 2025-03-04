#include<iostream>
#include<queue>
#include<stack>
using namespace std;

struct station //站點
{
	int cargoNum = 0; //站點中的貨物數
	queue<int>cargoArrivalPos; //可當成每個站點內都有貨物輸送帶，每個貨物上記載要被送去哪個站點
};

int main()
{
	int testCase, stationNum, truckCapacity, queueMax, cargoTotal = 0, time = 0; //測資、站點數、卡車容量、輸送帶最大容量、貨物總數、卡車總花費時間
	vector<station>stationQueue; //存所有站點的資料
	for (cin >> testCase; testCase--; stationQueue.clear(), time = 0) //每次跑下一輪測資前初始化
	{
		stationQueue.push_back(station()); //stationQueue[0]不使用
		cin >> stationNum >> truckCapacity >> queueMax; //輸入站點數、卡車容量、輸送帶最大容量
		stack<int>truck; //卡車(裡面的貨物以堆疊方式排列)
		for (int i = 1; i <= stationNum; i++)
		{
			stationQueue.push_back(station()); //每次新增一個站點
			cin >> stationQueue[i].cargoNum; //輸入該站點的貨物數
			cargoTotal += stationQueue[i].cargoNum; //加入貨物總數
			for (int input, k = stationQueue[i].cargoNum; k--;) //input == 貨物的輸送地點
			{
				cin >> input;
				stationQueue[i].cargoArrivalPos.push(input); //將貨物加入該站點的輸送帶中
			}
		}

		for (int pos = 1; cargoTotal; (pos %= stationNum)++, time += 2) //當前所在站點、在貨物還沒送完前、在所有站點間循環、兩站間的路程要2分鐘
		{
			//進站後卡車先卸貨。先確認卡車上有沒有貨，再判斷當前貨物的目的地是否為該站，或是輸送帶是否還有空間。每次卸貨要1分鐘
			for (; truck.size() && (truck.top() == pos || stationQueue[pos].cargoNum < queueMax); time++)
			{
				if (truck.top() == pos) //若當前貨物的目的地為當前站點
				{
					cargoTotal--; //直接卸貨而不需放入輸送帶，總貨物數 - 1
				}
				else //若輸送帶還有空間
				{
					stationQueue[pos].cargoArrivalPos.push(truck.top()); //將貨物放入輸送帶的最尾端
					stationQueue[pos].cargoNum++; //輸送帶上的貨物數 + 1
				}

				truck.pop(); //卡車卸貨
			}

			//再裝貨。先確認輸送帶上還有貨且卡車上還有空間，每次裝貨需要1分鐘
			for (; stationQueue[pos].cargoArrivalPos.size() && truck.size() < truckCapacity; time++)
			{
				truck.push(stationQueue[pos].cargoArrivalPos.front()); //將輸送帶最前面的貨物裝到卡車上
				stationQueue[pos].cargoArrivalPos.pop();
				stationQueue[pos].cargoNum--; //輸送帶上的貨物數 - 1
			}
		}

		cout << time - 2 << endl; //在最後判斷cargoTotal == 0跳出迴圈之前，time會先 + 2，但在此之前cargoTotal已 == 0，故實際time要 - 2
	}

	system("pause");
}