#include<iostream>
#include<string>
#include<map>
using namespace std;

int main()
{
	string word; //1.��J�]�t�^��½Ķ�Υ����y���B2.��J�����y���@��key�Ӭd��val
	map<string, string>dictionary; //key�񥼪��y���Aval��^��
	for (size_t pos; getline(cin, word), word != "";) //�إߦr��A�C������J�A�Y��J���O�u����enter
	{
		pos = word.find(' '); //�����Ů檺��m(2�y����J�ɤ����H�Ů�j�})		
		dictionary.insert({ word.substr(pos + 1,word.size() - (pos + 1)),word.substr(0, pos) });//�^���r��ä��O��Jmap��(substr(�_�l��m,����))
	}

	while (getline(cin, word)) //�Y�r�夺����J�������y���A�h��X�������^��½Ķ(count�^��key�bmap�����X�{����)
	{
		cout << (dictionary.count(word) ? dictionary[word] : "eh") << endl;
	}

	system("pause");
}