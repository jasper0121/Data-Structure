#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>>graph; //�إߦ��V��
vector<bool>node; //�����Ҧ��I���g�L�P�_���A

void dfs(int startPos, int& counter)
{
	for (int i = 0; i < graph[startPos].size(); i++) //�C���I���i��|���ƼƭӤ���s�V��L�I(��V)�A�C���N���I���Ҧ����䳣�չϨ��L�@�M
	{
		if (node[graph[startPos][i]] == false) //�Y���I�ҳs���U�@���I�٥����X�L
		{
			node[graph[startPos][i]] = true; //�h���U�ӱN���X���I�A�N���I���A�]��true
			dfs(graph[startPos][i], --counter); //���g�L���I�Ӽƥ� - 1�A�A�����I�~�򨫳X
		}
	}
}

int main()
{
	vector<int>start; //�s�Ҧ��n�i��dfs���_�l�I
	for (int nodeNum, startNum; cin >> nodeNum, nodeNum; graph.clear(), start.clear()) //�`�I�ӼơB�C���ndfs���_�l�ӼơF��J�h���X�F�C����l��
	{
		graph.resize(nodeNum + 1); //�]�w�}�C�j�p�A0����
		for (int y; cin >> y, y;) //�C����J�_�l�I�A��J0�h���X
		{
			for (int x; cin >> x, x; graph[y].push_back(x)); //�C����J���I�s�Jy���U�A�N��y �� x
		}

		cin >> startNum; //��J�n�]dfs�ɪ��_�I��
		start.resize(startNum); //�ھڰ_�I�Ƴ]�w�}�C�j�p
		for (int i = 0; i < startNum; cin >> start[i++]); //��J�Ҧ��_�I

		//�C����node���m(0���ΥB�Ҧ���l���A��false)�Bcounter == �������g�L���I�ӼơA�b�Ҧ��_�l�I�٨S���L���e
		for (int counter, i = 0; node.resize(nodeNum + 1), i < startNum; i++, node.clear(), cout << endl)
		{
			dfs(start[i], counter = nodeNum); //�]dfs(�C��counter��l���I�Ӽ�)�A�ت��D�X�C���qstart[i]�}�l����A�̲׵L�k���X�쪺�I�Ӽ�
			cout << counter; //��X�L�k���X�쪺�I�Ӽ�
			for (int i = 1; i < node.size(); i++) //�A�N�����I�@�@�L�X��
			{
				if (node[i] == false)
				{
					cout << " " << i;
				}
			}
		}
	}

	system("pause");
}