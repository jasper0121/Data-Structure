#include<iostream>
#include<stack>
using namespace std;

int main()
{
	for (int max; cin >> max, max;) //max == 車廂號碼的最大值 == 車廂數，若輸入0則跳出
	{
		int* input = new int[max + 1]; //0不用，存期望更改後的車廂排序
		while (cin >> input[1], input[1]) //輸入欲更改的車廂排列順序，先判斷第1個輸入是不是0
		{
			stack<int>coach; //存進站後暫存的車廂
			for (int i = 2; i <= max; cin >> input[i++]); //輸入剩下欲更改的車廂排列順序
			for (int index = 1, num = 1; index <= max;) //index == 欲先出站的車廂號碼，num == 當前車廂號碼，從進站的第1節車廂開始
			{
				if (num < input[index]) //若當前的車廂號碼 < 欲先出站的車廂號碼
				{
					coach.push(num++); //則先將當前的車廂存起來(車廂後進先出)
				}
				else if (num > input[index]) //若當前的車廂號碼 > 欲先出站的車廂號碼
				{
					if (coach.top() != input[index++]) //若當前將要拿出來的的車廂號碼和期望的不同
					{
						break; //代表期望的車廂順序無法實現，故跳出迴圈
					}

					coach.pop(); //則將先前存起來的車廂拿出來
				}
				else
				{
					num++, index++; //當前的車廂號碼 == 欲先出站的車廂號碼，繼續檢查下一個車廂
				}
			}

			cout << (coach.empty() ? "Yes\n" : "No\n"); //若期望的車廂順序可以實現，則暫存的空間應為0
		}

		cout << endl;
		delete[]input;
	}

	system("pause");
}