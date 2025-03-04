#include<iostream>
#include<deque>
using namespace std;

int main()
{
	int population, commandNum, citizen, caseNum = 1; //�`�H�ơB���O�ơB�����s���B��ecase��
	char command; //���O�B��JN��E
	//�إ�deque�F�C������J�`�H�ƩM���O�ơB�Y�H�ƩM���O�Ƴ��O0�h���X�F�C���M���W�������G
	for (deque<int>queue; cin >> population >> commandNum, population || commandNum; queue.clear())
	{
		for (int n = 1; n <= min(population, commandNum); n++) //�����s���q1�}�l��J����A��J�ƶq���`�H�ƩM���O�Ƥ����p���@��M�w
		{
			queue.push_back(n);
		}

		for (cout << "Case " << caseNum++ << ":\n"; commandNum--;)
		{
			if (cin >> command, command == 'N') //�C������J���O�A�Y���O��N
			{
				cout << queue[0] << endl; //�L�X�����1�ӤH���s��
				queue.push_back(queue[0]); //�A��L��춤��̫᭱
				queue.pop_front(); //�R����1��
			}
			else //�Y���O��E
			{
				cin >> citizen; //��J�s��
				for (deque<int>::iterator it = queue.begin(); it != queue.end(); it++) //�ˬd�ӽs�����S���s�b��e����̡A�Y���h�R��
				{
					if (*it == citizen)
					{
						queue.erase(it);
						break;
					}
				}

				queue.push_front(citizen); //�N�ӽs������̫e��
			}
		}
	}

	system("pause");
}