#include<iostream>
#include<iomanip>
#include<string>
#include<map>
using namespace::std;

int main()
{
	int testCase, total = 0; //�X�մ���
	string treeName; //�𪺺���
	cin >> testCase;
	cin.ignore(); //�M��cin���w�İ�
	getline(cin, treeName); //��Jenter����j��
	map<string, double>species; //�s�𪺦W�٤ξ𪺿�J����
	for (int k = 0; k < testCase; species.clear(), total = 0, k++) //�i�U�մ���e�Nspecies�Mtotal��l��
	{
		if (k != 0)
		{
			cout << endl;
		}

		for (; getline(cin, treeName), treeName != ""; total++) //�C������J�A�Y��J���O�u��enter
		{
			if (species.count(treeName)) //�Ymap���w�g����J����W(count == �^��key�bmap�����X�{���ơC�]key�ߤ@�A�G�^�ǳ̤j��1)
			{
				species[treeName]++; //�h��value + 1��ܸӾ𪺿�J����
			}
			else
			{
				species.insert({ treeName,1 }); //�_�h���J�A�]�t��W�M�Ӿ𪺿�J����
			}
		}

		for (map<string, double>::iterator it = species.begin(); it != species.end(); it++) //��X��e����W��J���Ʀ��`��J���ʤ���
		{
			//fixed == �ϱ��U�Ӫ�setprecision�u�@�Φb�p���I��Bsetprecision == ��4��ơA�̫�@��۰ʥ|�ˤ��J(�Y�e�S��fixed�h�]�t��Ƴ���)
			cout << it->first << " " << fixed << setprecision(4) << it->second / total * 100 << endl;
		}
	}

	system("pause");
}