#include<iostream>
#include<stack>
#include<map>
using namespace std;

int main()
{
	string input; //輸入英文字串
	multimap<int, stack<char>, greater<int>>container; //將每種stack的size由大排到小
	for (int testCase = 1; cin >> input, input != "end"; testCase++, container.clear()) //每次將multimap裡的資料清空
	{
		for (size_t i = 0; i < input.size(); i++) //將字串內的所有字元放入stack，所有stack內字元由小到大(A~Z)向上堆，題目求最大堆(size())的stack
		{
			stack<char> newStack; //每次建立新的stack來加入container中
			for (auto it = container.begin(); it != container.end(); it++) //每次從size最大的stack開始(auto可以自動推斷變數型態，在此相當於iterator)
			{
				if (it->second.top() < input[i]) //若找到stack的頂端字元 < input的當前字元
				{
					newStack = it->second; //則將該stack複製給newStack
					break; //已找到故跳出迴圈
				}
			}

			newStack.push(input[i]); //將當前字元加入newStack(若上面的for都找不到，則newStack裡只會有1個元素)
			container.insert({ newStack.size(),newStack }); //加入multimap排序(key == stack的size、value == stack)
		}

		cout << "Case " << testCase << ": " << container.begin()->first << endl; //輸出所有stack中size最大者
	}

	system("pause");
}