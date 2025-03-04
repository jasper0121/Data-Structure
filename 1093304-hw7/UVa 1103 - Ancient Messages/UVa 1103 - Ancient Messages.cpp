#include<iostream>
#include<vector>
#include<set>
using namespace std;

const string Bin[16]{ "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" }; //16��2�i��
const char word[6]{ 'W','A','K','J','S','D' }; //�H�Τ�r�����Ŭ}�ƹ����r��
vector<string>input, graph; //input == ��J�Ϫ���ơA�C�ӼƬ�16�i��Bgraph == �Ninput�ର2�i��A�æb�ഫ�᪺�ϥ|�P�A�[�@��~��

void dfs_erase_outside(int x, int y) //�M���H�Τ�r�~��dfs
{
	if (y < graph.size() && x < graph[y].size()) //�Yx�My���b�d��(�|���Nint�ন�Msize()�@�˪�size_t�A����A�G�Y��-1�h�|�ܦ��̤j��ƦӤ��X����)
	{
		if (graph[y][x] == '0') //�Y�J��r��0
		{
			graph[y][x] = ' '; //�h�N��אּ�ťաA���۩����I���|�P�~��dfs�A��H�Τ�r�~���r�����令�ť�
			dfs_erase_outside(x - 1, y); //��
			dfs_erase_outside(x, y - 1); //�W
			dfs_erase_outside(x + 1, y); //�k
			dfs_erase_outside(x, y + 1); //�U
		}
	}
}

void dfs_find_hole(int x, int y) //��H�Τ�r�����Ŭ}
{
	if (graph[y][x] == '0') //�Y�J��r��0
	{
		graph[y][x] = ' '; //�h�N��אּ�ť�
		dfs_find_hole(x - 1, y); //��
		dfs_find_hole(x, y - 1); //�W
		dfs_find_hole(x + 1, y); //�k
		dfs_find_hole(x, y + 1); //�U
	}
}

void dfs_search_word(int x, int y, int& counter) //���y��ӶH�Τ�r
{
	if (graph[y][x] == '1') //�Y�J��r��1
	{
		graph[y][x] = ' '; //�h�N��אּ�ť�
		dfs_search_word(x - 1, y, counter); //��
		dfs_search_word(x, y - 1, counter); //�W
		dfs_search_word(x + 1, y, counter); //�k
		dfs_search_word(x, y + 1, counter); //�U
	}

	if (graph[y][x] == '0') //�L�{���Y�J��r��0�A�N���e��m���H�Τ�r�����Ŭ}(�]�H�Τ�r�~��0���w���M��)
	{
		counter++; //counter + 1�A�Ŭ}�ƬO�P�O�H�Τ�r�������Ӧr��������
		dfs_find_hole(x, y); //�A�N�Ŭ}�����r��0�M��
	}
}

int main()
{
	multiset<char>output; //�D�حn�D��X�r���n�Ѥp��j�A��multiset�Ƨ�
	//numLine == ��J���r���(�Y����)�BnumChar == �r����סF�Y��J0�h���X�F�C����l��
	for (int numLine, numChar, testCase = 1; cin >> numLine >> numChar, numLine; input.clear(), graph.clear(), output.clear(), testCase++)
	{
		input.resize(numLine + 1); //�]�w�}�C�j�p�A0����
		graph.resize(numLine + 2, "0"); //�]�w�}�C�j�p�A�åB��l�b�C�椺��J�r��0�@�����ᰵdfs�ɪ�����ΡA+2���]�w[0]�M[size() - 1]���r�ꬰ��
		graph[0].resize(numChar * 4 + 2, '0'); //�]�w�W�����
		graph[graph.size() - 1] = graph[0]; //�U��P�z
		for (int y = 1; y < input.size(); graph[y++] += '0') //��J�r��A�ñN���ର�G�i��A�C���bgraph[y]���᭱��1��0��@�k��
		{
			cin >> input[y];
			for (int x = 0; x < numChar; x++)
			{
				graph[y] += Bin[input[y][x] - (isdigit(input[y][x]) ? '0' : 'a' - 10)]; //�䤤�N�r��0�ন�Ʀr0�A�Y�J��a ~ f�h�ন�Ʀr10 ~ 15
			}
		}

		dfs_erase_outside(0, 0); //���Ngraph���H�Τ�r�~�������M��
		for (int counter, x = 0, y = 1; y < graph.size(); x = 0, y++) //counter == �H�Τ�r�����Ŭ}��(�ӪŬ}�Ʀ��T�w�������r��)
		{
			while ((x = graph[y].find('1', x)) != -1) //�q�C�Ӧr��}�l��A�Y�����r��1(graph�����H�ιϮץ�'1'�զ�)
			{
				dfs_search_word(x++, y, counter = 0); //�h�N�䬰�_�I�]�j�M�H�Τ�r��dfs�A�C�����Ncounter�k�s�Adfs��qx + 1����m�~���U�@�ӶH�Τ�r
				output.insert(word[counter]); //�Ncounter���ন�۹������r���é�Jmultiset���Ѥp��j�Ƨ�
			}
		}

		cout << "Case " << testCase << ": ";
		for (auto it = output.begin(); it != output.end(); cout << *it++); //�L�Xoutput���Ҧ�����
		cout << endl;
	}

	system("pause");
}