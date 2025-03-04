#include<iostream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

struct node { int order = 0, low = 0; }; //�C�Ӹ`�I�������ǡA�Τ@�ӥi�l�Ҩ�̻��çΦ���������
vector<vector<int>>graph; //�L�V��
vector<node>point; //�O���C�@�I�����A
int cutPointNum = 0; //���I�ƶq(�Y�������I�A�h�Ϸ|������2�ӥH�W)

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
				point[cur].low = min(point[cur].low, point[graph[cur][x]].low); //�Y��e���Ilow�ȸ��j�A�h�N��אּchild��low��

				//�Y��e���I�D�ڥB�s�����䤤�@�Ӥl�N�A��low >=cur���`�I�s���A�N��Ӥl�N���l�𤤨S������@�I�s��cur���e�A���ɭY�Ncur�����h�|�ϹϤ���
				//�Y��e���I���ڡA�e���H�ڪ����A�]dfs�ҩ��ڦ�child�A�Gchild�ƥ� + 1�A�Ychild >= 2�h�N��ڬ����I
				if ((cur != par && point[cur].order <= point[graph[cur][x]].low) || (cur == par && ++rootChildNum == 2))
				{
					cutPoint = true;
				}
			}
		}
	}

	if (cutPoint) //�Y�����I
	{
		cutPointNum++; //�h���I�� + 1
	}
}

int main()
{
	string input; //��J����
	stringstream string_to_int; //�N�r�ꤤ���Ʀr�নint�A�C���H�Ů欰Ū�������I
	for (int nodeNum; cin >> nodeNum, nodeNum; graph.clear(), point.clear(), cutPointNum = 0) //��J�I�ӼơA�C����ƭ��m
	{
		graph.resize(nodeNum + 1); //�D�ت��`�I�s���̤p��1�A�G0����
		point.resize(nodeNum + 1); //�}�C�j�p���Hgraph
		for (int start, end; cin >> start, start; string_to_int.clear()) //�]�D�ؿ�J�Mstart�s����end�Ƥ��T�w�A�B�C�ӼƦr���H�Ů�j�}�A�G�ϥ�stringstream
		{
			cin.ignore(); //�b�e���T�wstart����0��A�]����n�Mgetline�V�ΡA�G���M��cin���Ȧs�ϥH�קK��J���~
			getline(cin, input); //�N���᪺�ƭ�end���H�r��覡��J
			for (string_to_int << input; !string_to_int.eof();) //�Ninput��Jstringstream�ഫ��int�F�bŪ��r�굲�����e
			{
				string_to_int >> end; //�C���N�Ů�e�����নint��end
				graph[start].push_back(end); //�صL�V��
				graph[end].push_back(start);
			}
		}

		for (int time, y = 1; y < graph.size(); y++) //�]dfs�A�Ҧ��I�ˬd�@��
		{
			if (point[y].order == 0) //�Y���I��order == 0
			{
				dfs_find_cut_point(y, y, time = 1); //�N����I�٨S�����L�A�H����root�]dfs��cut point
			}
		}

		cout << cutPointNum << endl; //�D�D���I��
	}

	system("pause");
}