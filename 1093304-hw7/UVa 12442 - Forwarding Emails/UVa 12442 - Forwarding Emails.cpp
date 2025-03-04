#include<iostream>
#include<vector>
using namespace std;

vector<int>sentEmail; //�����e�H��H�Aindex�H�H��value
vector<bool>node; //���X���A

void dfs(int startPos, int& counter)
{
	node[startPos] = true; //�C���N��e����m�]��true�A�N���I�w���X(�i�J�U��testCase�e���|��s)
	if (sentEmail[startPos]) //�Y�H�n�e�쪺���I�٥��Q���X
	{
		int temp = sentEmail[startPos]; //�h���N�ؼ��I�s�_��
		sentEmail[startPos] = 0; //�ؼ��I�]��0�N��w���X(�U�@�檺dfs�����h�ȴN�|�^�_)
		dfs(temp, ++counter); //��counter + 1��A�Htemp�~��dfs
		sentEmail[startPos] = temp; //dfs��N���٦^�h
	}
}

int main()
{
	int testCase, nodeNum, input; //����ơB�I�ӼơB
	cin >> testCase;
	for (int t = 1; testCase--; t++, sentEmail.clear(), node.clear()) //�C����l��
	{
		cin >> nodeNum; //��J�I�Ӽ�
		sentEmail.resize(nodeNum + 1); //�إ߰}�C�j�p�A0����
		node.resize(nodeNum + 1); //�إ߰}�C�j�p�A0����
		for (int i, n = sentEmail.size() - 1; n--;) //��J�H�H�H�M���H�H(index �� value)
		{
			cin >> i >> input;
			sentEmail[i] = input;
		}

		int minIndex = nodeNum, max = 0; //�D�بD�Ĥ@�ʫH�H���֯�ϳ̦h�H�ݨ�(max�P�h��index���p��)
		for (int counter, k = 1; k < sentEmail.size(); k++) //counter�O���Ӧ�dfs���X�L�X���I
		{
			if (node[k] == false) //�Y���I�٥��Q���X(�Y���I�b���e�w���X�L�A�h�N��@���_�I��dfs�᪺counter���w�p��max�A�Y���P�_�|�ɭP�W��)
			{
				dfs(k, counter = 1); //�C��dfs�e�Ncounter�]��1(�n��J�_�l�I)
				if (counter > max) //�]index�Ѥp��j�}�ldfs�A�G�u�ݦҼ{max�Y�i
				{
					max = counter;
					minIndex = k;
				}
			}
		}

		cout << "Case " << t << ": " << minIndex << endl;
	}
}