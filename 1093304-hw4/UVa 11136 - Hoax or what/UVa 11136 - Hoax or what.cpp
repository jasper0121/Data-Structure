#include<iostream>
#include<set>
using namespace std;

int main()
{
	size_t day, num_of_bills, amount, total = 0; //���ʤѼơB�b��(�����)�`�ơB�浧�b����B�B�x���X���B
	for (multiset<int>bill; cin >> day, day; bill.clear(), total = 0) //�إ߱b�檺multiset(1��key�i�H���h��val)�B�C������J���ʤѼơB�C���b��Mtotal��l��
	{
		for (; day--; bill.erase(bill.begin()), bill.erase(--bill.end())) //���ʴ������C�ѩ���B�̤p�M�̤j(day���K��l��)�B�C���R����2���b��
		{
			for (cin >> num_of_bills; num_of_bills--;) //����J�ӤѦ��X���b��(num_of_bills���K��l��)�B�C����J�浧�b����B�ô��J
			{
				cin >> amount;
				bill.insert(amount);
			}

			total += *--bill.end() - *bill.begin(); //�x���`��X == ���ʴ������C�ѵ������c�����̤j���B�t(end() == �̫�@�Ӫ��U�@�ӡA�G�n�O�o��--)
		}

		cout << total << endl;
	}

	system("pause");
}