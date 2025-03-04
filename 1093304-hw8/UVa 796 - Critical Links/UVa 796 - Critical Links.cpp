#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct node { int order = 0, low = 0; }; //�C�Ӹ`�I�������ǡA�Τ@�ӥi�l�Ҩ�̻��çΦ���������
vector<vector<int>>graph; //�L�V��
vector<node>point; //�O���C�@�I�����A
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> output; //�Yfirst�P�A�h�|���second�A�ƧǤ覡�����ݭȳ̤p

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
		output.push({ min(cur, par),max(cur, par) }); //cur�Mpar�����s�������A�D�D�I���s���Ѥp��j�A�Y��1���I�s���ۦP�h�H���2���I�Ѥp��j
	}
}

int main()
{
	char buf; //��J�A����
	for (int nodeNum; cin >> nodeNum; cout << endl, graph.clear(), point.clear()) //�I�ӼơF�C����ƭ��m
	{
		graph.resize(nodeNum); //�ϥ�0�A�]�D�ئ��s����0���`�I
		point.resize(nodeNum); //�}�C�j�p���Hgraph
		for (int x, y; nodeNum--;) //��J����ëصL�V��
		{
			cin >> y >> buf >> x >> buf;
			while (x--)
			{
				graph[y].push_back(int()); //�C�����b�̫�W�[�@��
				cin >> graph[y].back(); //�A�N��ƿ�J�Ӯ椤�A�Ӧ]����|���Ҧ��I���s�����p�A�G�u�ݫس�V�Y�i�A�̫�ا����N�|�O���V��
			}
		}

		for (int time, y = 0; y < graph.size(); y++) //�]dfs�A�Ҧ��I�ˬd�@��
		{
			if (point[y].order == 0) //�Y���I��order == 0
			{
				dfs_find_bridge(y, y, time = 1); //�N����I�٨S�����L�A�H����root�]dfs��bridge
			}
		}

		for (cout << output.size() << " critical links\n"; output.size(); output.pop()) //�N�Ҧ����G��X(���ݬ��̤p)
		{
			cout << output.top().first << " - " << output.top().second << endl;
		}
	}

	system("pause");
}