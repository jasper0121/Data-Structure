#include<iostream>
#include<queue>
using namespace std;

int main()
{
	for (size_t testCase, input, sum = 0; cin >> testCase, testCase; sum = 0) //�C������J���X������A�Y��J0�h���X�F�C�����m�W���[�`���G
	{
		priority_queue<int, vector<int>, greater<int>>numbers; //priority_queue�S��clear()�A�G�ŧi�b�j�餺�F���A��int���ݭ����Fgreater�Otop()���̤p
		while (testCase--) //�ھڴ���ơA�C����J�ô��J�s����
		{
			cin >> input;
			numbers.push(input);
		}

		for (int twoMin = 0; numbers.size() != 1;) //�C���N�̤p��2�ӼƬۥ[�A�A�N���`�M�[�Jnumbers�Msum���F�Ynumbers���u��1�Ӽƫh���X
		{
			twoMin = numbers.top();
			numbers.pop();
			twoMin += numbers.top();
			numbers.pop();
			numbers.push(twoMin);
			sum += twoMin;
		}

		cout << sum << endl; //��X���G
	}

	system("pause");
}