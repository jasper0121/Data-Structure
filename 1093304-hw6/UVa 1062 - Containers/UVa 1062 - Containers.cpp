#include<iostream>
#include<stack>
#include<map>
using namespace std;

int main()
{
	string input; //��J�^��r��
	multimap<int, stack<char>, greater<int>>container; //�N�C��stack��size�Ѥj�ƨ�p
	for (int testCase = 1; cin >> input, input != "end"; testCase++, container.clear()) //�C���Nmultimap�̪���ƲM��
	{
		for (size_t i = 0; i < input.size(); i++) //�N�r�ꤺ���Ҧ��r����Jstack�A�Ҧ�stack���r���Ѥp��j(A~Z)�V�W��A�D�بD�̤j��(size())��stack
		{
			stack<char> newStack; //�C���إ߷s��stack�ӥ[�Jcontainer��
			for (auto it = container.begin(); it != container.end(); it++) //�C���qsize�̤j��stack�}�l(auto�i�H�۰ʱ��_�ܼƫ��A�A�b���۷��iterator)
			{
				if (it->second.top() < input[i]) //�Y���stack�����ݦr�� < input����e�r��
				{
					newStack = it->second; //�h�N��stack�ƻs��newStack
					break; //�w���G���X�j��
				}
			}

			newStack.push(input[i]); //�N��e�r���[�JnewStack(�Y�W����for���䤣��A�hnewStack�̥u�|��1�Ӥ���)
			container.insert({ newStack.size(),newStack }); //�[�Jmultimap�Ƨ�(key == stack��size�Bvalue == stack)
		}

		cout << "Case " << testCase << ": " << container.begin()->first << endl; //��X�Ҧ�stack��size�̤j��
	}

	system("pause");
}