#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct node { int order = 0, low = 0; }; //�C�Ӹ`�I�������ǡA�Τ@�ӥi�l�Ҩ�̻��çΦ���������
vector<vector<int>>graph; //�L�V��
vector<node>point; //�O���C�@�I�����A
vector<pair<int, int>>output; //�����cut point��Ҥ������ϭӼơAfirst == �I���s���Bsecond == �������ϭӼơF��lfirst == index�A����ƧǷ|����

bool comp(const pair<int, int>& left, const pair<int, int>& right) //�D�D�N�������ϼ�(second)�Ѥj��p�ƧǡA�Y�ۦP�h�H�I�s��(first)�Ѥp��j�Ƨ�
{
	return left.second == right.second ? left.first<right.first : left.second>right.second;
}

void dfs_find_cut_point(int cur, int par, int& time) //current�Bparent�B���ǰO��
{
	bool cutPoint = false; //��e���I�O�_�����I
	int rootChildNum = 0; //root��child��(���]�A�Hback edge�s�^�Ӫ��I)�A�Y����2�hroot�����I
	point[cur].order = point[cur].low = time++; //�C���������ǰO���N��w���L
	for (int x = 0; x < graph[cur].size(); x++) //�ˬd�M��e�s�����Ҧ��I
	{
		if (graph[cur][x] != par) //�Y���U�ӭn���X���I���Oparent(�Y��if���ˬd�B�h�|��cur�Mpar�����s����back edge�ӾɭP���~)
		{
			if (point[graph[cur][x]].order) //�p�G�U�@�ӭn���X��order���O0�A�N��U�@���I�w���X�L
			{
				point[cur].low = min(point[cur].low, point[graph[cur][x]].order); //�Y�U�@�ӭn���X���`�I�s�����p�A�h�N��ȵ���e��low
			}
			else
			{
				dfs_find_cut_point(graph[cur][x], cur, time); //�Ϥ��N��U�@���I�٨S���X�L�A�~��]dfs
				point[cur].low = min(point[cur].low, point[graph[cur][x]].low); //�Y��e���Ilow�ȸ��j�A�h�N��令child��low��

				//�Y��e���I�D�ڥB�s�����䤤�@�Ӥl�N�A��low >=cur���`�I�s���A�N��Ӥl�N���l�𤤨S������@�I�s��cur���e�A���ɭY�Ncur�����h�|�ϹϤ���
				//�Y��e���I���ڡA�e���H�ڪ����A�]dfs�ҩ��ڦ�child�A�Gchild�ƥ� + 1�A�Ychild >= 2�h�N��ڬ����I
				if ((cur != par && point[cur].order <= point[graph[cur][x]].low) || (cur == par && ++rootChildNum == 2))
				{
					output[cur].second++; //�C�����󦨥ߡA�N���U���I�Ө�cur�O���I�A�̫�output[cur].second == �cut point��Ҥ������L�V�ϼ�
				}
			}
		}
	}
}

int main()
{
	for (int station, target; cin >> station >> target, station; cout << endl, graph.clear(), point.clear(), output.clear()) //target == ��X����
	{
		graph.resize(station);
		point.resize(station);
		for (int i = 0; i < station; output.push_back({ i++ , 1 })); //output�j�p == station�ơA�����I���ܤַ|����1�ӵL�V��
		for (int x, y; cin >> y >> x, y != -1;) //��J����ëصL�V�ϡA�Y��J-1�h���X
		{
			graph[y].push_back(x);
			graph[x].push_back(y);
		}

		for (int time, y = 0; y < graph.size(); y++) //�]dfs�A�Ҧ��I�ˬd�@��
		{
			if (point[y].order == 0) //�Y���I��order == 0
			{
				dfs_find_cut_point(y, y, time = 1); //�N����I�٨S�����L�A�H����root�]dfs��cut point
			}
		}

		sort(output.begin(), output.end(), comp); //�ھ��D�ةҨD�Noutput�Ƨ�
		for (int i = 0; i < target; i++) //�L�X�etarget�ƪ�����
		{
			cout << output[i].first << " " << output[i].second << endl;
		}
	}

	system("pause");
}