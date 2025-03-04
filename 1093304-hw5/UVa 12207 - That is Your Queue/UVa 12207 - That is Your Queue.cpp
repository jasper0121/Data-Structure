#include<iostream>
#include<deque>
using namespace std;

int main()
{
	int population, commandNum, citizen, caseNum = 1; //總人數、指令數、市民編號、當前case數
	char command; //指令、輸入N或E
	//建立deque；每次先輸入總人數和指令數、若人數和指令數都是0則跳出；每次清除上次的結果
	for (deque<int>queue; cin >> population >> commandNum, population || commandNum; queue.clear())
	{
		for (int n = 1; n <= min(population, commandNum); n++) //市民編號從1開始放入隊伍，放入數量由總人數和指令數中較小的一方決定
		{
			queue.push_back(n);
		}

		for (cout << "Case " << caseNum++ << ":\n"; commandNum--;)
		{
			if (cin >> command, command == 'N') //每次先輸入指令，若指令為N
			{
				cout << queue[0] << endl; //印出隊伍中第1個人的編號
				queue.push_back(queue[0]); //再把他放到隊伍最後面
				queue.pop_front(); //刪除第1個
			}
			else //若指令為E
			{
				cin >> citizen; //輸入編號
				for (deque<int>::iterator it = queue.begin(); it != queue.end(); it++) //檢查該編號有沒有存在當前隊伍裡，若有則刪除
				{
					if (*it == citizen)
					{
						queue.erase(it);
						break;
					}
				}

				queue.push_front(citizen); //將該編號移到最前面
			}
		}
	}

	system("pause");
}