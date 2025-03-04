#include<iostream>
#include<vector>
#include<set>
using namespace std;

int main()
{
	int testCase, bf, sg, sb, atk; //�X�մ���B�Գ���(battlefields)�B��x�B�ŭx�A�����O
	multiset<int, greater<int>>greenArmy, blueArmy; //�s����x�O(��w�]set����O���Ubegin()�̤p�A�k�U--end()�̤j�A���[greater�Ϥ�����)
	cin >> testCase;
	for (int k = 0; k < testCase; greenArmy.clear(), blueArmy.clear(), k++)
	{
		if (k != 0) //�@�}�l���n����
		{
			cout << endl;
		}

		//�ԤO�t�m-----------------------------------------------------------------------------------------------------------
		cin >> bf >> sg >> sb; //��J�Գ��ơB��x�H�ơB�ŭx�H��
		while (sg--) //��J��x�������O�զ�(���K��sg��l��)
		{
			cin >> atk;
			greenArmy.insert(atk);
		}

		while (sb--) //��J�ŭx�������O�զ�(���K��sb��l��)
		{
			cin >> atk;
			blueArmy.insert(atk);
		}

		//�԰�----------------------------------------------------------------------------------------------------------------
		for (vector<int>battle; greenArmy.size() != 0 && blueArmy.size() != 0; battle.clear()) //�]�߾Գ��B�Y���賣�٦��Ѿl�ԤO
		{
			//�C�������ԡA����bf�Ӧ^�X�A�Y������@��x�O���ūh�԰���������(battle��size�|��bf��)
			for (int i = 0; i < bf && !(greenArmy.empty() || blueArmy.empty()); i++)
			{
				battle.insert(battle.end(), *greenArmy.begin() - *blueArmy.begin()); //�ԤO�۴�æs�Jbattle��
				greenArmy.erase(greenArmy.begin());
				blueArmy.erase(blueArmy.begin());
			}

			for (int i = 0; i < battle.size(); i++)
			{
				if (battle[i] > 0) //�Ybattle[i]���Ȭ����A�h��xĹ
				{
					greenArmy.insert(battle[i]);
				}
				else if (battle[i] < 0) //�Ybattle[i]���Ȭ����A�h�ŭxĹ
				{
					blueArmy.insert(-battle[i]);
				}
			}
		}

		//�ӭt----------------------------------------------------------------------------------------------------------------
		if (greenArmy.size() != 0) //�Y��x���Ѿl
		{
			cout << "green wins\n";
			for (multiset<int>::iterator it = greenArmy.begin(); it != greenArmy.end(); it++) //�L�X�Ѿl�ԤO
			{
				cout << *it << endl;
			}
		}
		else if (blueArmy.size() != 0) //�Y�ŭx���Ѿl
		{
			cout << "blue wins\n";
			for (multiset<int>::iterator it = blueArmy.begin(); it != blueArmy.end(); it++) //�L�X�Ѿl�ԤO
			{
				cout << *it << endl;
			}
		}
		else
		{
			cout << "green and blue died\n";
		}
	}

	system("pause");
}