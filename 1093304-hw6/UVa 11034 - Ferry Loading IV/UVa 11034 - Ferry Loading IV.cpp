#include<iostream>
#include<queue>
using namespace std;

int main()
{
	int testCase, shipLength, carNum, carLength, counter = 0; //����ơB�����(����)�B�����`�ơB��������(����)�B���e����
	string side; //�e���B��Jleft��right
	for (cin >> testCase; testCase--; counter = 0) //�C����e���ƭ��m
	{
		queue<int>carQueue[2]; //�e���⩤���ݪ������A0 == �����B1 == �k��
		cin >> shipLength >> carNum; //��J����שM���l�`��
		shipLength *= 100; //�����ऽ��
		for (int n = carNum; n--;)
		{
			cin >> carLength >> side; //��J���l���שM�b�e�����Υk��
			side == "left" ? carQueue[0].push(carLength) : carQueue[1].push(carLength); //�ھڨ�����m�N�ƾک�J�۹�����queue
		}

		for (int i = 0; carQueue[0].size() || carQueue[1].size(); ++i %= 2, counter++) //�Y�ܤ֦��@���٦����A�C�����e���� + 1
		{
			for (int capacity = shipLength; carQueue[i].size() && capacity >= carQueue[i].front();) //�Y�ө��٦������s�b�B�Y���ٮe�Ǳo�U��e����
			{
				capacity -= carQueue[i].front(); //��e������J��A�G��Ŷ����
				carQueue[i].pop(); //�Ө��q�������R��
			}
		}

		cout << counter << endl; //��X���e����
	}

	system("pause");
}