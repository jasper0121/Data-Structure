#include<iostream>
#include<queue>
using namespace std;

int main()
{
	int testCase, command, value, counter = 3; //����ơB���O(��J1��2)�B��J�Ψ��X���ȡB3�ظ�Ƶ��c���p�ƾ�(true���Ӽ�)
	//��deque����stack�Mqueue���欰�F�C����J����ơF�C���M�ŤW�������G�Mcounter��l��
	for (deque<int>stack, queue; cin >> testCase; stack.clear(), queue.clear(), counter = 3)
	{	
		priority_queue<int>priorityQueue; //priority_queue�S��clear()�G�ŧi�b�j�餺�B�x�s���A��int���ݭ����B�w�]��less(top()���ȳ̤j)
		bool stackMode = true, queueMode = true, priorityQueueMode = true; //3�ظ�Ƶ��c�����A
		while (testCase--)
		{
			cin >> command >> value; //�C����J���O�M��
			if (command == 1) //�Y���O��1�A�h�N�ȴ��J3�ظ�Ƶ��c��
			{
				stack.push_back(value);
				queue.push_back(value);
				priorityQueue.push(value);
			}
			else
			{
				if (stackMode) //�Ystack�����A��true
				{
					if (stack.empty() || value != stack.back()) //�Y��estack���ũ�value�Mstack�����̫�@�ӼƤ��ۦP
					{
						stackMode = false; //�N���J���欰���Ostack�A�G�]��false
						counter--; //true���Ӽ� - 1
					}
					else
					{
						stack.pop_back(); //�_�h�N�̫�@�ӼƧR��(�����Ndeque���̫��stack��top()�ӹF����i���X)
					}
				}

				if (queueMode) //�Yqueue�����A��true
				{
					if (queue.empty() || value != queue.front()) //�Y��equeue���ũ�value�Mqueue�����Ĥ@�ӼƤ��ۦP
					{
						queueMode = false; //�N���J���欰���Oqueue�A�G�]��false
						counter--; //true���Ӽ� - 1
					}
					else
					{
						queue.pop_front(); //�_�h�N�Ĥ@�ӼƧR��(�������i���X)
					}
				}

				if (priorityQueueMode) //�YpriorityQueue�����A��true
				{
					if (priorityQueue.empty() || value != priorityQueue.top()) //�Y��epriorityQueue���ũ�value�MpriorityQueue��top()���ۦP
					{
						priorityQueueMode = false; //�N���J���欰���OpriorityQueue�A�G�]��false
						counter--; //true���Ӽ� - 1
					}
					else
					{
						priorityQueue.pop(); //�_�h�Ntop()�R��
					}
				}
			}
		}

		if (counter == 0) //�N��3�ظ�Ƶ��c�ҩM��J���欰���P
		{
			cout << "impossible\n";
		}
		else if (counter == 1) //�L�X��J���欰�ŦX���ظ�Ƶ��c
		{
			if (stackMode)
			{
				cout << "stack\n";
			}
			else if (queueMode)
			{
				cout << "queue\n";
			}
			else
			{
				cout << "priority queue\n";
			}
		}
		else //�N��2�إH�W����Ƶ��c�ŦX��J���欰
		{
			cout << "not sure\n";
		}
	}

	system("pause");
}