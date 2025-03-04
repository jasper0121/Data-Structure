#include<iostream>
#include<queue>
using namespace std;

int main()
{
	int testCase, command, value, counter = 3; //測資數、指令(輸入1或2)、放入或取出的值、3種資料結構的計數器(true的個數)
	//用deque模擬stack和queue的行為；每次輸入測資數；每次清空上次的結果和counter初始化
	for (deque<int>stack, queue; cin >> testCase; stack.clear(), queue.clear(), counter = 3)
	{	
		priority_queue<int>priorityQueue; //priority_queue沒有clear()故宣告在迴圈內、儲存型態為int不需重載、預設為less(top()的值最大)
		bool stackMode = true, queueMode = true, priorityQueueMode = true; //3種資料結構的狀態
		while (testCase--)
		{
			cin >> command >> value; //每次輸入指令和值
			if (command == 1) //若指令為1，則將值插入3種資料結構中
			{
				stack.push_back(value);
				queue.push_back(value);
				priorityQueue.push(value);
			}
			else
			{
				if (stackMode) //若stack的狀態為true
				{
					if (stack.empty() || value != stack.back()) //若當前stack為空或value和stack內的最後一個數不相同
					{
						stackMode = false; //代表輸入的行為不是stack，故設為false
						counter--; //true的個數 - 1
					}
					else
					{
						stack.pop_back(); //否則將最後一個數刪除(模擬將deque的最後當成stack的top()來達成後進先出)
					}
				}

				if (queueMode) //若queue的狀態為true
				{
					if (queue.empty() || value != queue.front()) //若當前queue為空或value和queue內的第一個數不相同
					{
						queueMode = false; //代表輸入的行為不是queue，故設為false
						counter--; //true的個數 - 1
					}
					else
					{
						queue.pop_front(); //否則將第一個數刪除(模擬先進先出)
					}
				}

				if (priorityQueueMode) //若priorityQueue的狀態為true
				{
					if (priorityQueue.empty() || value != priorityQueue.top()) //若當前priorityQueue為空或value和priorityQueue的top()不相同
					{
						priorityQueueMode = false; //代表輸入的行為不是priorityQueue，故設為false
						counter--; //true的個數 - 1
					}
					else
					{
						priorityQueue.pop(); //否則將top()刪除
					}
				}
			}
		}

		if (counter == 0) //代表3種資料結構皆和輸入的行為不同
		{
			cout << "impossible\n";
		}
		else if (counter == 1) //印出輸入的行為符合哪種資料結構
		{
			if (stackMode)
			{
				cout << "stack\n";
			}
			else if (queueMode)
			{
				cout << "queue\n";
			}
			else
			{
				cout << "priority queue\n";
			}
		}
		else //代表有2種以上的資料結構符合輸入的行為
		{
			cout << "not sure\n";
		}
	}

	system("pause");
}