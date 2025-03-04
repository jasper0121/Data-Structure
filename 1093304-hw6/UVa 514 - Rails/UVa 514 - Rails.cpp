#include<iostream>
#include<stack>
using namespace std;

int main()
{
	for (int max; cin >> max, max;) //max == ���[���X���̤j�� == ���[�ơA�Y��J0�h���X
	{
		int* input = new int[max + 1]; //0���ΡA�s������᪺���[�Ƨ�
		while (cin >> input[1], input[1]) //��J����諸���[�ƦC���ǡA���P�_��1�ӿ�J�O���O0
		{
			stack<int>coach; //�s�i����Ȧs�����[
			for (int i = 2; i <= max; cin >> input[i++]); //��J�ѤU����諸���[�ƦC����
			for (int index = 1, num = 1; index <= max;) //index == �����X�������[���X�Anum == ��e���[���X�A�q�i������1�`���[�}�l
			{
				if (num < input[index]) //�Y��e�����[���X < �����X�������[���X
				{
					coach.push(num++); //�h���N��e�����[�s�_��(���[��i���X)
				}
				else if (num > input[index]) //�Y��e�����[���X > �����X�������[���X
				{
					if (coach.top() != input[index++]) //�Y��e�N�n���X�Ӫ������[���X�M���檺���P
					{
						break; //�N����檺���[���ǵL�k��{�A�G���X�j��
					}

					coach.pop(); //�h�N���e�s�_�Ӫ����[���X��
				}
				else
				{
					num++, index++; //��e�����[���X == �����X�������[���X�A�~���ˬd�U�@�Ө��[
				}
			}

			cout << (coach.empty() ? "Yes\n" : "No\n"); //�Y���檺���[���ǥi�H��{�A�h�Ȧs���Ŷ�����0
		}

		cout << endl;
		delete[]input;
	}

	system("pause");
}