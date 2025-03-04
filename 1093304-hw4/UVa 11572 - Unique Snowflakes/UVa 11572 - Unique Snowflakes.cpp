#include<iostream>
#include<set>
using namespace std;

int main()
{
	int testCase, num, first = 0, len = 0, max = 0; //�X�մ���B����ƶq�B�ƦC���_�l��m�B��e�ƦC���סB�ƦC���̤j����(���ƦC���Ʀr�����ƥB����J����)
	int* type = new int[1000000]; //�������(�D�ػ��������|�W�L100�U��)
	set<int> snowflakes; //�ֳt�d�ߦ��L���Ƴ��������
	for (cin >> testCase; testCase--; snowflakes.clear(), first = len = max = 0) //��J���X�մ���B�C��first,len,max��l��
	{
		cin >> num; //��J���h�ֳ���
		for (int a = 0; a < num; a++) //��J�������
		{
			cin >> type[a];
		}

		for (int cur = 0; cur < num; cur++) //��X�ƦC���̤j����
		{
			for (; snowflakes.count(type[cur]); first++, len--) //�Y�n���J���Ȥw�s�b��e�ƦC�d�򤤡B�C���_�l��m�|����A�۹�a���פ]�|���
			{
				snowflakes.erase(type[first]); //�h�@���R����ӭȤ��b�ƦC�d�򤺬���
			}

			snowflakes.insert(type[cur]);
			if (++len > max) //�C�����J�s���ƫ���׷| + 1�A�Y��e���ƦC���׬��̤j
			{
				max = len; //�h�N���װO���U��
			}
		}

		cout << max << endl; //�̫��X�ƦC���̤j����
	}

	delete[] type; //�R���ʺA�}�C
	system("pause");
}