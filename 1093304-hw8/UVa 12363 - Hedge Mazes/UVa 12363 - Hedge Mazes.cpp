#include<iostream>
#include<vector>
using namespace std;

struct node { int order = 0, low = 0; }; //�C�Ӹ`�I�������ǡA�Τ@�ӥi�l�Ҩ�̻��çΦ���������
vector<vector<int>>graph; //�L�V��
vector<node>point; //�O���C�@�I�����A
vector<int>bridge; //�O�����A�bindex(current)�̦sparent

void dfs_find_bridge(int cur, int par, int& time) //current�Bparent�B���ǰO��(�i�Ncur�Mpar����������cur���@����)
{
	point[cur].order = point[cur].low = time++; //�C���������ǰO���N��w���L
	for (int x = 0; x < graph[cur].size(); x++) //�ˬd�M��e�s�����Ҧ��I
	{
		if (graph[cur][x] != par) //�Y���U�ӭn���X���I���Oparent(�Y��if���ˬd�B�h�|��cur�Mpar�����s����back edge�ӾɭP���~)
		{
			if (point[graph[cur][x]].order == 0) //�p�G�U�@�ӭn���X��order�O0
			{
				dfs_find_bridge(graph[cur][x], cur, time); //�N��U�@���I�٨S���X�L�A�~��]dfs
			}

			//�Y��e���Ilow�ȸ��j�A�h�N��low�ȧ令child��low�ȡA�Ϥ��P�z�C�`���N�O2�̪�low�ɥi�ब�ۨ��̤p
			(point[cur].low > point[graph[cur][x]].low) ? (point[cur].low = point[graph[cur][x]].low) : (point[graph[cur][x]].low = point[cur].low);
		}
	}

	if (cur != par && point[cur].order == point[cur].low) //�Y�Droot�Bcur��order == low�A�N��cur�S������l�N���s��par���e�ӧΦ���
	{
		bridge[par] = bridge[cur] = par; //cur�Mpar�����s�������Aoutput����cur�Mpar��m������par�A�@������n���ìd���ϥ�(par�O�ۤv��parent)
	}
}

int find_root(int child) //�ìd���A��child����
{
	return bridge[child] == child ? child : find_root(bridge[child]); //�Ychild���ȩMindex�P�A�N��child�Oroot�F�_�h�~��V�W��
}

int main()
{
	//�ж��ơB���Y�ơB�d�ߦ��ơF�C����ƭ��m
	for (int room, corridor, query; cin >> room >> corridor >> query, room; cout << "-\n", graph.clear(), point.clear(), bridge.clear())
	{
		graph.resize(room + 1); //�D�ت��`�I�s���̤p��1�A�G0����
		point.resize(room + 1); //�}�C�j�p���Hgraph
		bridge.resize(room + 1); //�ϸ`�I�s�����۹���index�A�G0����
		for (int x, y; corridor--;) //��J����ëصL�V��
		{
			cin >> y >> x;
			graph[y].push_back(x);
			graph[x].push_back(y);
		}

		for (int time, y = 1; y < graph.size(); y++) //�]dfs�A�Ҧ��I�ˬd�@��
		{
			if (point[y].order == 0) //�Y���I��order == 0
			{
				dfs_find_bridge(y, y, time = 1); //�N����I�٨S�����L�A�H����root�]dfs��bridge
			}
		}

		for (int start, end, startRoot, endRoot; query--;) //�D�D�qstart��end��_�u�ǥѨ����Ө�F�A�d��query��
		{
			cin >> start >> end;
			//�_�I�M���I���O�V�W������ۤv��root�A�Yroot�ۦP�A�N��i�H�qstart����end
			cout << ((startRoot = find_root(start)) && (endRoot = find_root(end)) && startRoot == endRoot ? "Y\n" : "N\n");
		}
	}

	system("pause");
}