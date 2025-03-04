#include<iostream>
#include<vector>
#include<set>
using namespace std;

struct node { int order = 0, low = 0; }; //���ǡB�i�l�Ҫ��̤p�I
vector<vector<int>>graph; //�L�V��
vector<node>point; //�O���C�@�I�����A
vector<bool>cutPoint; //�O���C���I�O���Ocut point
vector<set<int>>component;
vector<pair<int, int>>inStack; //��vector����stack�ӼȦs�bdfs�ɩҸg�L���I

void dfs_biconnected_component(int cur, int par, int& time) //�I���s�q���q
{
	int rootChildNum = 0; //�کҳs����child(���]�A�Hback edge�s�����`�I)
	point[cur].order = point[cur].low = time++; //�C���������ǰO���N��w���L
	for (int x = 0; x < graph[cur].size(); x++) //�ˬd�M��e�s�����Ҧ��I
	{
		if (graph[cur][x] != par) //�Y���U�ӭn���X���I���Oparent
		{
			if (point[graph[cur][x]].order) //�p�G�U�@�ӭn���X��order���O0�A�N��U�@���I�w���X�L
			{
				point[cur].low = min(point[cur].low, point[graph[cur][x]].order); //�Y�U�@�ӭn���X���`�I�s�����p�A�h�N��ȵ���e��low
			}
			else
			{
				rootChildNum++;
				inStack.push_back({ cur, graph[cur][x] }); //�b�i��dfs�e���N��e��edge�s�_��
				dfs_biconnected_component(graph[cur][x], cur, time); //�U�@���I�٨S���X�L�A�~��]dfs
				point[cur].low = min(point[cur].low, point[graph[cur][x]].low); //�Y��e���Ilow�ȸ��j�A�h�N��令child��low��
				//�Y��e���I�s�����䤤�@�Ӥl�N�A��low >=cur���`�I�s���A�N��Ӥl�N���l�𤤨S������@�I�s��cur���e�A���ɭY�Ncur�����h�|�ϹϤ���
				if (point[cur].order <=point[graph[cur][x]].low )
				{
					cutPoint[cur] = true; //�N���e���I�Ocut point
					component.push_back(set<int>()); //�W�[1��H�scomponent���U�ظ`�I
					pair<int, int>temp; //�Ȧs
					do
					{
						temp = inStack.back(); //�C������stack��top
						inStack.pop_back(); //stack��pop
						component.back().insert(temp.first); //�s�J2�I
						component.back().insert(temp.second);
					} while (temp != pair<int, int>(cur, graph[cur][x])); //�@��pop��̫�X�Ӫ��O��e����A�L�{����pop�X�Ӫ������Ҭ��P��component
				}
			}
		}
	}

	if (cur == par && rootChildNum < 2) //�̫��ˬd�A�Y�ڪ�child < 2�N��ګDcut point
	{
		cutPoint[cur] = false;
	}
}

int main()
{
	for (int tunnel, time, testCase = 1; cin >> tunnel, tunnel; component.clear()) //�G�D�ơA�C���Ncomponent����ƲM��
	{
		graph.assign(tunnel + 2, vector<int>()); //0���ΡA�B�`�I�� == �G�D�� + 1(�@���u�i�����Y��2�I)�A�G�}�C�Ŷ��� == tunnel + 2
		point.assign(tunnel + 2, node()); //0���ΡA�B�`�I�� == �G�D�� + 1
		cutPoint.assign(tunnel + 2, false); //0���ΡA�B�`�I�� == �G�D�� + 1
		for (int x, y; tunnel--;) //�صL�V��
		{
			cin >> y >> x;
			graph[y].push_back(x);
			graph[x].push_back(y);
		}

		dfs_biconnected_component(1, 1, time = 1); //�Ҧ��`�I���۳s���A�G�H�`�I1�}�l�]dfs�Y�i
		if (component.size() == 1) //�Ycomponent�u��1��
		{
			//�N��Lcut point�A�ֶ̤��]�m2�I�A�B��k�Ƭ�C��n��2�A��²�� == n (n - 1) / 2
			cout << "Case " << testCase++ << ": " << 2 << " " << component[0].size() * (component[0].size() - 1) / 2 << endl; //��X�D�حn�D
			continue;
		}

		long long int minChoice = 0, total = 1; //�Ϥ��Y��2�ӥH�Wcomponent�A�]�̤p��ܪ��I�ӼơB�`��k��
		for (int i = 0; i < component.size(); i++)
		{
			int cpNum = 0; //��ecomponent����cut point�ƶq
			for (auto it = component[i].begin(); it != component[i].end(); it++) //��Ҧ���component
			{
				if (cutPoint[*it]) //�Y��e���V���I�Ocut point
				{
					cpNum++; //�hcut point�ƶq + 1
				}
			}

			if (cpNum == 1) //�Y��e��component�u��1��cut point
			{
				minChoice++; //�h�n�b��component����ܤ@�I
				total *= component[i].size() - 1; //�N��e��cut point����L�I���_��
			}
		}

		cout << "Case " << testCase++ << ": " << minChoice << " " << total << endl; //��X�D�حn�D
	}

	system("pause");
}