#include<iostream>
#include<queue>
#include<stack>
using namespace std;

struct station //���I
{
	int cargoNum = 0; //���I�����f����
	queue<int>cargoArrivalPos; //�i���C�ӯ��I�������f����e�a�A�C�ӳf���W�O���n�Q�e�h���ӯ��I
};

int main()
{
	int testCase, stationNum, truckCapacity, queueMax, cargoTotal = 0, time = 0; //����B���I�ơB�d���e�q�B��e�a�̤j�e�q�B�f���`�ơB�d���`��O�ɶ�
	vector<station>stationQueue; //�s�Ҧ����I�����
	for (cin >> testCase; testCase--; stationQueue.clear(), time = 0) //�C���]�U�@������e��l��
	{
		stationQueue.push_back(station()); //stationQueue[0]���ϥ�
		cin >> stationNum >> truckCapacity >> queueMax; //��J���I�ơB�d���e�q�B��e�a�̤j�e�q
		stack<int>truck; //�d��(�̭����f���H���|�覡�ƦC)
		for (int i = 1; i <= stationNum; i++)
		{
			stationQueue.push_back(station()); //�C���s�W�@�ӯ��I
			cin >> stationQueue[i].cargoNum; //��J�ӯ��I���f����
			cargoTotal += stationQueue[i].cargoNum; //�[�J�f���`��
			for (int input, k = stationQueue[i].cargoNum; k--;) //input == �f������e�a�I
			{
				cin >> input;
				stationQueue[i].cargoArrivalPos.push(input); //�N�f���[�J�ӯ��I����e�a��
			}
		}

		for (int pos = 1; cargoTotal; (pos %= stationNum)++, time += 2) //��e�Ҧb���I�B�b�f���٨S�e���e�B�b�Ҧ����I���`���B�⯸�������{�n2����
		{
			//�i����d�������f�C���T�{�d���W���S���f�A�A�P�_��e�f�����ت��a�O�_���ӯ��A�άO��e�a�O�_�٦��Ŷ��C�C�����f�n1����
			for (; truck.size() && (truck.top() == pos || stationQueue[pos].cargoNum < queueMax); time++)
			{
				if (truck.top() == pos) //�Y��e�f�����ت��a����e���I
				{
					cargoTotal--; //�������f�Ӥ��ݩ�J��e�a�A�`�f���� - 1
				}
				else //�Y��e�a�٦��Ŷ�
				{
					stationQueue[pos].cargoArrivalPos.push(truck.top()); //�N�f����J��e�a���̧���
					stationQueue[pos].cargoNum++; //��e�a�W���f���� + 1
				}

				truck.pop(); //�d�����f
			}

			//�A�˳f�C���T�{��e�a�W�٦��f�B�d���W�٦��Ŷ��A�C���˳f�ݭn1����
			for (; stationQueue[pos].cargoArrivalPos.size() && truck.size() < truckCapacity; time++)
			{
				truck.push(stationQueue[pos].cargoArrivalPos.front()); //�N��e�a�̫e�����f���˨�d���W
				stationQueue[pos].cargoArrivalPos.pop();
				stationQueue[pos].cargoNum--; //��e�a�W���f���� - 1
			}
		}

		cout << time - 2 << endl; //�b�̫�P�_cargoTotal == 0���X�j�餧�e�Atime�|�� + 2�A���b�����ecargoTotal�w == 0�A�G���time�n - 2
	}

	system("pause");
}