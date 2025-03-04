#include<iostream>
#include<list>
using namespace std;

int main()
{
	list<string>output; //存輸出結果，用list方便快速插入or刪除
	for (string input; cin >> input; output.clear()) //每次清空上次的結果
	{
		list<string>::iterator it = output.insert(output.end(), ""); //先增加一個node (內容為空字串)，並建立一個iterator指向它
		for (int k = 0; k < input.size(); k++)
		{
			switch (input[k]) //每次檢查string內當前的字元
			{
			case'[': //若當前的字元是'['，則接下來的字串放在當前字串的前面			
				it = (*output.begin() == "") ? output.begin() : output.insert(output.begin(), ""); //若最前面的node內容為空，則不需要增加新node以節省空間
				break;
			case']': //若當前的字元是']'，則接下來的字串放在當前字串的後面
				it = (*--output.end() == "") ? --output.end() : output.insert(output.end(), ""); //若最後面的node內容為空，則不需要增加新node以節省空間
				break;
			default:
				*it += input[k]; //當前字元加入相對應的字串中
			}
		}

		for (it = output.begin(); it != output.end(); cout << *it++); //it再改指output的第1個node，每次印出node內的字串直到it指向end()
		cout << endl;
	}

	system("pause");
}