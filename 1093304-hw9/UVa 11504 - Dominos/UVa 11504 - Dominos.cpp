#include<iostream>
#include<vector>
using namespace std;

struct node { int order = 0, low = 0, cpn = 0; }; //���ǡB�i�l�Ҫ��̤p�I�B���ݪ�component�s��
vector<vector<int>>graph; //���V��
vector<node>point; //�O���C�@�I�����A
vector<int>inStack; //��vector����stack�ӼȦs�bdfs�ɩҸg�L���I
int cpnNum = 0; //component�s���A�̫᪺�ȥi��@component��

void dfs_strong_connect_component(int cur, int& time)
{
	point[cur].order = point[cur].low = time++; //�C���������ǰO���N��w���L
	inStack.push_back(cur); //�C�����N��e���I��Jstack
	for (int x = 0; x < graph[cur].size(); x++)
	{
		if (point[graph[cur][x]].order) //�p�G�U�@�ӭn���X��order���O0�A�N��U�@���I�w���X�L
		{
			for (int i = 0; i < inStack.size(); i++)
			{
				if (inStack[i] == graph[cur][x]) //�Y�U���I���bstack�̭��A�N��i�Φ�component(�Y���V�Ϫ���)
				{
					point[cur].low = min(point[cur].low, point[graph[cur][x]].order); //�Y�U�@�ӭn���X���`�I�s�����p�A�h�N��ȵ���e��low
					break;
				}
			}
		}
		else
		{
			dfs_strong_connect_component(graph[cur][x], time); //�Ϥ��N��U�@���I�٨S���X�L�A�~��]dfs
			point[cur].low = min(point[cur].low, point[graph[cur][x]].low); //�Y��e���Ilow�ȸ��j�A�h�N��令child��low��
		}
	}

	if (point[cur].order == point[cur].low) //�̫��ˬd�A�Y���󦨥ߡA�N���I�Ocut point
	{
		int temp; //�Ȧs
		do
		{
			temp = inStack.back(); //�C������stack��top
			inStack.pop_back(); //stack��pop
			point[temp].cpn = cpnNum; //�N�C��component�s��(�q0�}�l)�A�N�P�s�����I�����@�I(�Y�Y�I������)
		} while (temp != cur); //�@��pop��̫�pop�X�Ӫ��Ocut point�A�L�{����pop�X�Ӫ������Ҭ��P��component
		cpnNum++;
	}
}

int main()
{
	vector<bool>component;
	int testCase, nodeNum, link, ans = 0; //����ơB�I�ӼơB��B����
	for (cin >> testCase; testCase--; cpnNum = ans = 0)
	{
		cin >> nodeNum >> link;
		graph.assign(nodeNum + 1, vector<int>()); //0����
		point.assign(nodeNum + 1, node()); //0����
		for (int x, y; link--;) //�ئ��V��
		{
			cin >> y >> x;
			graph[y].push_back(x);
		}

		for (int time, y = 1; y < graph.size(); y++) //��Φ�����component
		{
			if (point[y].order == 0)
			{
				dfs_strong_connect_component(y, time = 1);
			}
		}

		component.assign(cpnNum, true); //�̫�cpnNum����== component���ƶq�A�H���إ߰}�C�j�p(�w�]���]true�A�Y�w�]��e�Ҧ��I���i��@�_�l�I)
		for (int y = 1; y < graph.size(); y++) //�ˬd�Ҧ���e���I���V�t�@�I
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				if (point[y].cpn != point[graph[y][x]].cpn) //�Y2�I�����ݪ�component�s�����P
				{
					//�N��ؼ��I(graph[y][x])��component�B��"�Q���J"���A�A�G�ؼ�component�������N�I�����@�����P�ɪ�"�_�l�I"
					component[point[graph[y][x]].cpn] = false; //e.x :�]2��cpn�s����1�M2�C�Y���󦨥ߡA�N��s�b1 �� 2�A�Y����1�������N�I�A�h2�]�|�Q�v�T
				}
			}
		}

		for (int i = 0; i < component.size(); i++) //�̫�p�⦳�h��component�i��@�_�l�I
		{
			if (component[i]) //�Y��true�h�N��i��@�_�l�I
			{
				ans++;
			}
		}

		cout << ans << endl;
	}

	system("pause");
}