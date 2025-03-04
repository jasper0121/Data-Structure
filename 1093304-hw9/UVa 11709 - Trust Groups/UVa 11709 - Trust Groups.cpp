#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

struct node { int order = 0, low = 0; }; //���ǡB�i�l�Ҫ��̤p�I
vector<vector<int>>graph; //���V��
vector<node>point; //�O���C�@�I�����A
vector<int>inStack; //��vector����stack�ӼȦs�bdfs�ɩҸg�L���I
map<string, int>name; //�N�r���ন�����Ʀr
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
		//�@��pop��̫�pop�X�Ӫ��Ocut point�A�L�{����pop�X�Ӫ������Ҭ��P��component
		for (int temp; temp = inStack.back(), inStack.pop_back(), temp != cur;); //�Ȧs�A�C������stack��top�Bstack��pop
		cpnNum++;
	}
}

int main()
{
	string input; //��J�W�r
	for (int people, link; cin >> people >> link, people; name.clear(), cpnNum = 0) //�I�B��F�C����l��
	{
		cin.ignore(); //cin�N�Mgetline�V�ΡA���Ncin���Ȧs�ϲM��
		graph.assign(people, vector<int>()); //�إ߰}�C�j�p(assign�]�tclear)
		point.assign(people, node()); //�إ߰}�C�j�p(assign�]�tclear)
		for (int n = 0; people--; n++) //��J�Ҧ��W�r�ñN��s��
		{
			getline(cin, input);
			name.insert({ input ,n });
		}

		for (string start, end; link--;) //�ئ��V��
		{
			getline(cin, start);
			getline(cin, end);
			graph[name[start]].push_back(name[end]);
		}

		for (int time, y = 0; y < graph.size(); y++) //��Φ�����component
		{
			if (point[y].order == 0)
			{
				dfs_strong_connect_component(y, time = 1);
			}
		}

		cout << cpnNum << endl; //���רDcomponent��
	}

	system("pause");
}