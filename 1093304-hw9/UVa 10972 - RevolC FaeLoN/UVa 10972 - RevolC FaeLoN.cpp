#include<iostream>
#include<vector>
using namespace std;

struct node { int order = 0, low = 0, cpn = 0; }; //���ǡB�i�l�Ҫ��̤p�I�B���ݪ�component�s��
vector<vector<int>>graph; //�L�V��
vector<node>point; //�O���C�@�I�����A
vector<int>inStack; //��vector����stack�ӼȦs�bdfs�ɩҸg�L���I
int cpnNum = 0; //component�s���A�̫᪺�ȥi��@component��

void dfs_bridge_component(int cur, int par, int& time)
{
	point[cur].order = point[cur].low = time++; //�C���������ǰO���N��w���L
	inStack.push_back(cur); //�C�����N��e���I��Jstack
	for (int x = 0; x < graph[cur].size(); x++) //�ˬd�M��e�s�����Ҧ��I
	{
		if (graph[cur][x] != par) //�Y���U�ӭn���X���I���Oparent(�Y��if���ˬd�B�h�|��cur�Mpar�����s����back edge�ӾɭP���~)
		{
			if (point[graph[cur][x]].order == 0) //�p�G�U�@�ӭn���X��order�O0
			{
				dfs_bridge_component(graph[cur][x], cur, time); //�N��U�@���I�٨S���X�L�A�~��]dfs
			}

			//�Y��e���Ilow�ȸ��j�A�h�N��low�ȧ令child��low�ȡA�Ϥ��P�z�C�`���N�O2�̪�low�ɥi�ब�ۨ��̤p
			(point[cur].low > point[graph[cur][x]].low) ? (point[cur].low = point[graph[cur][x]].low) : (point[graph[cur][x]].low = point[cur].low);
		}
	}

	if (point[cur].order == point[cur].low) //�̫��ˬd�A�Y���󦨥ߡA�N���I�Obridge
	{
		int temp; //�Ȧs
		do
		{
			temp = inStack.back(); //�C������stack��top
			inStack.pop_back(); //stack��pop
			point[temp].cpn = cpnNum; //�N�C��component�s��(�q0�}�l)�A�N�P�s�����I�����@�I(�Y�Y�I������)
		} while (temp != cur); //�@��pop��̫�X�Ӫ��Ocut point�A�L�{����pop�X�Ӫ������Ҭ��P��component
		cpnNum++;
	}
}

int main()
{
	vector<int>component;
	for (int nodeNum, road; cin >> nodeNum >> road; cpnNum = 0) //�I�B��F�C����l��
	{
		graph.assign(nodeNum + 1, vector<int>()); //0����
		point.assign(nodeNum + 1, node()); //0����
		for (int x, y; road--;) //�صL�V��
		{
			cin >> y >> x;
			graph[y].push_back(x);
			graph[x].push_back(y);
		}

		for (int time, y = 1; y < graph.size(); y++) //��bridge component
		{
			if (point[y].order == 0)
			{
				dfs_bridge_component(y, y, time = 1); //�N����I�٨S�����L�A�H����root�]dfs��bridge component
			}
		}

		if (cpnNum == 1) //�Y�u��1��component
		{
			cout << 0 << endl; //�h�L�V�令���V�ϫ�A���ݭn�B�~�[�D��
			continue;
		}

		component.assign(cpnNum, 0); //�HcpnNum�إ߰}�C�j�p�Avalue�N��Ҧ��I(component�Y�I)�P��L�I���X���s��
		for (int y = 1; y < graph.size(); y++)
		{
			for (int x = 0; x < graph[y].size(); x++)
			{
				if (point[y].cpn != point[graph[y][x]].cpn) //�Y2�I�����ݪ�component�s�����P
				{
					component[point[y].cpn]++; //�N���e��component���s�X�h1����A�G + 1
				}
			}
		}

		int alonePoint = 0, leaf = 0; //��W�I(�S���P��L�s����component�]��b��)�A���l�`�I
		for (int i = 0; i < component.size(); i++)
		{
			switch (component[i]) //���Ҧ���component
			{
			case 0: //�Y��0�A�N����W�I
				alonePoint++;
				break;
			case 1: //�Y��1�A�N�����l�`�I
				leaf++;
			}
		}

		//���1����A�Yleaf == 2�A�h�ݭn1����N2�I�s�����B�Yleaf == 3�A�h�ݭn2����N3�I�s�����A�G��(leaf + 1) / 2
		//���1���I�A�i�����N�I���J�Y���𤤪���A�h��|����2���A�i�N�䤤1����alonePoint�Ҵ��ѡA�GalonePoint����*2
		cout << (leaf + 1) / 2 + alonePoint << endl;
	}

	system("pause");
}