#include<iostream>
#include<stack>
using namespace std;

string input, output; //output == 更改字元順序的input

void dfs(int in, int out, string process, stack<char>temp) //in == input當前的index、out同理、process == 字串更改順序的過程
{
	if (process.size() == input.size() * 4) //process長度 == input + output + 每個i或o後面皆以一個空白鍵區隔 == input(或output)長度的4倍
	{
		process.pop_back(); //所求的process最後會多出一個空白鍵，故先將最後的空白鍵刪除
		cout << process << endl; //印出所求
		return;
	}

	if (in < input.size())
	{
		temp.push(input[in]); //將input當前的字元存入暫存
		dfs(in + 1, out, process + "i ", temp); //input當前的index + 1，i代表將字元存入暫存，繼續跑遞迴(i的總數 == input的長度)
		temp.pop(); //temp頂端的字元已跑過上一行的dfs，故刪除
	}

	if (temp.size() && temp.top() == output[out]) //若暫存不為空且若暫存頂端的字元和output當前index的字元相同
	{
		temp.pop(); //將暫存頂端的字元刪除
		dfs(in, out + 1, process + "o ", temp); //output當前的index + 1，o代表將字元從暫存取出，繼續跑遞迴(o的總數 == output的長度)
	}
}

int main()
{
	while (cin >> input >> output)
	{
		stack<char>temp; //字元的暫存
		cout << "[\n";
		if (input.size() == output.size()) //若輸入和輸出的字串長度相同
		{
			dfs(0, 0, "", temp); //代表input可能可以更改字元順序變成output，跑dfs深度優先搜尋(因題目求更改順序的所有可能過程)
		}

		cout << "]\n";
	}

	system("pause");
}