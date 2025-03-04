#include<iostream>
#include<vector>
#include<set>
using namespace std;

const string Bin[16]{ "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" }; //16轉2進位
const char word[6]{ 'W','A','K','J','S','D' }; //象形文字中的空洞數對應字母
vector<string>input, graph; //input == 輸入圖的資料，每個數為16進位、graph == 將input轉為2進位，並在轉換後的圖四周再加一圈外牆

void dfs_erase_outside(int x, int y) //清除象形文字外的dfs
{
	if (y < graph.size() && x < graph[y].size()) //若x和y都在範圍內(會先將int轉成和size()一樣的size_t再比較，故若為-1則會變成最大整數而不合條件)
	{
		if (graph[y][x] == '0') //若遇到字元0
		{
			graph[y][x] = ' '; //則將其改為空白，接著往該點的四周繼續dfs，把象形文字外的字元都改成空白
			dfs_erase_outside(x - 1, y); //左
			dfs_erase_outside(x, y - 1); //上
			dfs_erase_outside(x + 1, y); //右
			dfs_erase_outside(x, y + 1); //下
		}
	}
}

void dfs_find_hole(int x, int y) //找象形文字內的空洞
{
	if (graph[y][x] == '0') //若遇到字元0
	{
		graph[y][x] = ' '; //則將其改為空白
		dfs_find_hole(x - 1, y); //左
		dfs_find_hole(x, y - 1); //上
		dfs_find_hole(x + 1, y); //右
		dfs_find_hole(x, y + 1); //下
	}
}

void dfs_search_word(int x, int y, int& counter) //掃描整個象形文字
{
	if (graph[y][x] == '1') //若遇到字元1
	{
		graph[y][x] = ' '; //則將其改為空白
		dfs_search_word(x - 1, y, counter); //左
		dfs_search_word(x, y - 1, counter); //上
		dfs_search_word(x + 1, y, counter); //右
		dfs_search_word(x, y + 1, counter); //下
	}

	if (graph[y][x] == '0') //過程中若遇到字元0，代表當前位置為象形文字內的空洞(因象形文字外的0都已先清掉)
	{
		counter++; //counter + 1，空洞數是判別象形文字對應哪個字母的關鍵
		dfs_find_hole(x, y); //再將空洞內的字元0清掉
	}
}

int main()
{
	multiset<char>output; //題目要求輸出字母要由小到大，用multiset排序
	//numLine == 輸入的字串數(即高度)、numChar == 字串長度；若輸入0則跳出；每次初始化
	for (int numLine, numChar, testCase = 1; cin >> numLine >> numChar, numLine; input.clear(), graph.clear(), output.clear(), testCase++)
	{
		input.resize(numLine + 1); //設定陣列大小，0不用
		graph.resize(numLine + 2, "0"); //設定陣列大小，並且初始在每格內放入字串0作為往後做dfs時的左牆用，+2為設定[0]和[size() - 1]的字串為牆
		graph[0].resize(numChar * 4 + 2, '0'); //設定上牆長度
		graph[graph.size() - 1] = graph[0]; //下牆同理
		for (int y = 1; y < input.size(); graph[y++] += '0') //輸入字串，並將其轉為二進位，每次在graph[y]的後面補1個0當作右牆
		{
			cin >> input[y];
			for (int x = 0; x < numChar; x++)
			{
				graph[y] += Bin[input[y][x] - (isdigit(input[y][x]) ? '0' : 'a' - 10)]; //其中將字元0轉成數字0，若遇到a ~ f則轉成數字10 ~ 15
			}
		}

		dfs_erase_outside(0, 0); //先將graph中象形文字外的部分清掉
		for (int counter, x = 0, y = 1; y < graph.size(); x = 0, y++) //counter == 象形文字內的空洞數(而空洞數有固定的對應字母)
		{
			while ((x = graph[y].find('1', x)) != -1) //從每個字串開始找，若有找到字元1(graph中的象形圖案由'1'組成)
			{
				dfs_search_word(x++, y, counter = 0); //則將其為起點跑搜尋象形文字的dfs，每次先將counter歸零，dfs後從x + 1的位置繼續找下一個象形文字
				output.insert(word[counter]); //將counter數轉成相對應的字母並放入multiset中由小到大排序
			}
		}

		cout << "Case " << testCase << ": ";
		for (auto it = output.begin(); it != output.end(); cout << *it++); //印出output中所有的值
		cout << endl;
	}

	system("pause");
}