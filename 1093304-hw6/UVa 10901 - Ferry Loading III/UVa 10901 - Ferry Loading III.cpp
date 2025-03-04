#include<iostream>
#include<queue>
#include<map>
using namespace std;

struct car
{
	int num = 0, distance = 0; //���l����J���ǡB���l���e�����Z��(�}��e���Ҫ�O���ɶ�)
}input;

int main()
{
	int testCase, shipCapacity, shipSpendTime, carNum, shipTotalTime = 0; //����ơB��e�q�B���e���ɶ��B�����`�ơB��`��O�ɶ�
	string side; //�e���B��Jleft��right
	multimap<int, int>output; //key == ���l����J���ǡBvalue == ���l�q�@�}�l���e�Ҫ�O���ɶ�
	for (cin >> testCase; testCase--; shipTotalTime = 0, output.clear())
	{
		queue<car>carQueue[2]; //�e���⩤���ݪ������A0 == �����B1 == �k��
		cin >> shipCapacity >> shipSpendTime >> carNum; //��e�q�B���e���ɶ��B�����`��
		for (int i = 0; i < carNum; i++)
		{
			input.num = i; //�᭱�|�N���ǥ��áA���D�حn�D��X���ǩM��J�n�ۦP�A�G������J����
			cin >> input.distance >> side; //��J���e�����Z���M�b�e�����@��
			side == "left" ? carQueue[0].push(input) : carQueue[1].push(input); //�ھڨ�����m�N�ƾک�J�۹�����queue
		}

		for (int i = 0; carQueue[0].size() || carQueue[1].size(); ++i %= 2) //i == ���e�Ҧb���A�Y�ܤ֦��@���٦���
		{
			if (carQueue[i].size() && carQueue[(i + 1) % 2].size()) //�Y�⩤������
			{
				if (shipTotalTime < min(carQueue[i].front().distance, carQueue[(i + 1) % 2].front().distance)) //�Y��`��O�ɶ� < �Z���e�����u����
				{
					shipTotalTime = min(carQueue[i].front().distance, carQueue[(i + 1) % 2].front().distance); //�h�Z�����p���@���@��`��O�ɶ�
				}
			}
			else //�Y���䤤�@���S����
			{
				if (carQueue[i].size()) //�Y���e�Ҧb���e������(�賓�L��)
				{
					if (carQueue[i].front().distance > shipTotalTime) //�Y���l�쩤�Z�����j
					{
						shipTotalTime = carQueue[i].front().distance; //�h�N�ӶZ����@��`��O�ɶ�(�۷�����l�쩤)
					}
				}
				else //�Y���e�Ҧb���e���L��(�賓����)
				{
					if (carQueue[(i + 1) % 2].front().distance > shipTotalTime) //�Y���l�쩤�Z�����j
					{
						shipTotalTime = carQueue[(i + 1) % 2].front().distance; //�h�N�ӶZ����@��`��O�ɶ�(�۷�����l�쩤)
					}
				}
			}

			//��e�C�Y���٦��Ŷ��B��e�e���٦������B�w�����쩤��
			for (int c = shipCapacity; c-- && carQueue[i].size() && shipTotalTime >= carQueue[i].front().distance;)
			{
				output.insert({ carQueue[i].front().num,shipTotalTime + shipSpendTime }); //�N�Ө�����ƥ[�Jmultimap���A��e�٭n�[�WshipSpendTime
				carQueue[i].pop(); //���w��e�A�q�������R��
			}

			shipTotalTime += shipSpendTime; //��e��N��e���ɶ��[�J�`��O�ɶ�
		}

		for (auto it = output.begin(); it != output.end(); it++) //auto == multimap<int, int>::iterator
		{
			cout << it->second << endl; //�L�X�Ҧ�����e�L�{�Ҫ�O���ɶ�
		}

		if (testCase) //�̫᪺testCase���n����
		{
			cout << endl;
		}
	}

	system("pause");
}