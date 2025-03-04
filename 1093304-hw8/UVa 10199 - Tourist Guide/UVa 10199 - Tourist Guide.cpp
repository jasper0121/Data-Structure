#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

struct node { int order = 0, low = 0; }; //�C�Ӹ`�I�������ǡA�Τ@�ӥi�l�Ҩ�̻��çΦ���������
vector<vector<int>>graph; //�L�V��
vector<node>point; //�O���C�@�I�����A
map<string, const int>placeName; //�s�a�W�M���@�ӹ����s��
set<string>output; //�Ҧ��Q��cut point���a�W

void dfs_find_cut_point(int cur, int par, int& time) //current�Bparent
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
					cutPoint = true;
				}
			}
		}
	}

	if (cutPoint) //�Y�����I
	{
		for (auto it = placeName.begin(); it != placeName.end(); it++) //�N���I��^�۹������r��
		{
			if (cur == it->second)
			{
				output.insert(it->first); //�D�حn�D�r���X�Ӷ��ǡA�G�N��s�Jset���Ƨ�
				break;
			}
		}
	}
}

int main()
{
	string inputName; //��J�a�W
	for (int placeNum, roadNum, testCase = 1; cin >> placeNum, placeNum; graph.clear(), point.clear(), placeName.clear(), output.clear())
	{
		graph.resize(placeNum);
		point.resize(placeNum);
		for (int n = 0; n < placeNum; n++) //��J�a�W�õ����������s���s�Jmap
		{
			cin >> inputName;
			placeName.insert({ inputName,n });
		}

		cin >> roadNum; //��J�D����
		for (string start, end; roadNum--;) //��J����ëصL�V��(�N�a�W�ন�������s��)
		{
			cin >> start >> end;
			graph[placeName[start]].push_back(placeName[end]);
			graph[placeName[end]].push_back(placeName[start]);
		}

		for (int time, y = 0; y < graph.size(); y++) //�]dfs�A�Ҧ��I�ˬd�@��
		{
			if (point[y].order == 0) //�Y���I��order == 0
			{
				dfs_find_cut_point(y, y, time = 1); //�N����I�٨S�����L�A�H����root�]dfs��cut point
			}
		}

		if (testCase != 1) //����1������~�A�C�������X�e���Ť@��
		{
			cout << endl;
		}

		cout << "City map #" << testCase++ << ": " << output.size() << " camera(s) found\n";
		for (auto it = output.begin(); it != output.end(); cout << *it++ << endl); //��X�@�����I���a�W(��X���ǥ�A ~ Z�ѵu���)
	}

	system("pause");
}