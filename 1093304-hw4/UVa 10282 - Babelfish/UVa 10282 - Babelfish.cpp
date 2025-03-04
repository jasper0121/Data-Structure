#include<iostream>
#include<string>
#include<map>
using namespace std;

int main()
{
	string word; //1.輸入包含英文翻譯及未知語言、2.輸入未知語言作為key來查找val
	map<string, string>dictionary; //key放未知語言，val放英文
	for (size_t pos; getline(cin, word), word != "";) //建立字典，每次先輸入，若輸入不是只有按enter
	{
		pos = word.find(' '); //先找到空格的位置(2語言輸入時中間以空格隔開)		
		dictionary.insert({ word.substr(pos + 1,word.size() - (pos + 1)),word.substr(0, pos) });//擷取字串並分別放入map中(substr(起始位置,長度))
	}

	while (getline(cin, word)) //若字典內有輸入的未知語言，則輸出對應的英文翻譯(count回傳key在map中的出現次數)
	{
		cout << (dictionary.count(word) ? dictionary[word] : "eh") << endl;
	}

	system("pause");
}