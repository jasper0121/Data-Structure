#include<iostream>
#include<list>
using namespace std;

int main()
{
	list<string>output; //�s��X���G�A��list��K�ֳt���Jor�R��
	for (string input; cin >> input; output.clear()) //�C���M�ŤW�������G
	{
		list<string>::iterator it = output.insert(output.end(), ""); //���W�[�@��node (���e���Ŧr��)�A�ëإߤ@��iterator���V��
		for (int k = 0; k < input.size(); k++)
		{
			switch (input[k]) //�C���ˬdstring����e���r��
			{
			case'[': //�Y��e���r���O'['�A�h���U�Ӫ��r���b��e�r�ꪺ�e��			
				it = (*output.begin() == "") ? output.begin() : output.insert(output.begin(), ""); //�Y�̫e����node���e���šA�h���ݭn�W�[�snode�H�`�٪Ŷ�
				break;
			case']': //�Y��e���r���O']'�A�h���U�Ӫ��r���b��e�r�ꪺ�᭱
				it = (*--output.end() == "") ? --output.end() : output.insert(output.end(), ""); //�Y�̫᭱��node���e���šA�h���ݭn�W�[�snode�H�`�٪Ŷ�
				break;
			default:
				*it += input[k]; //��e�r���[�J�۹������r�ꤤ
			}
		}

		for (it = output.begin(); it != output.end(); cout << *it++); //it�A���output����1��node�A�C���L�Xnode�����r�ꪽ��it���Vend()
		cout << endl;
	}

	system("pause");
}