#include<iostream>
#include<queue>
using namespace std;

int main()
{
	for (size_t testCase, input, sum = 0; cin >> testCase, testCase; sum = 0) //每次先輸入有幾筆測資，若輸入0則跳出；每次重置上次加總結果
	{
		priority_queue<int, vector<int>, greater<int>>numbers; //priority_queue沒有clear()，故宣告在迴圈內；型態為int不需重載；greater令top()為最小
		while (testCase--) //根據測資數，每次輸入並插入新的值
		{
			cin >> input;
			numbers.push(input);
		}

		for (int twoMin = 0; numbers.size() != 1;) //每次將最小的2個數相加，再將其總和加入numbers和sum中；若numbers內只剩1個數則跳出
		{
			twoMin = numbers.top();
			numbers.pop();
			twoMin += numbers.top();
			numbers.pop();
			numbers.push(twoMin);
			sum += twoMin;
		}

		cout << sum << endl; //輸出結果
	}

	system("pause");
}