#include<iostream>
#include<vector>
using namespace std;

vector<int>sentEmail; //紀錄送信對象，index寄信給value
vector<bool>node; //走訪狀態

void dfs(int startPos, int& counter)
{
	node[startPos] = true; //每次將當前的位置設為true，代表此點已走訪(進入下個testCase前不會刷新)
	if (sentEmail[startPos]) //若信要送到的該點還未被走訪
	{
		int temp = sentEmail[startPos]; //則先將目標點存起來
		sentEmail[startPos] = 0; //目標點設為0代表已走訪(下一行的dfs結束則值就會回復)
		dfs(temp, ++counter); //先counter + 1後，以temp繼續做dfs
		sentEmail[startPos] = temp; //dfs後將值還回去
	}
}

int main()
{
	int testCase, nodeNum, input; //測資數、點個數、
	cin >> testCase;
	for (int t = 1; testCase--; t++, sentEmail.clear(), node.clear()) //每次初始化
	{
		cin >> nodeNum; //輸入點個數
		sentEmail.resize(nodeNum + 1); //建立陣列大小，0不用
		node.resize(nodeNum + 1); //建立陣列大小，0不用
		for (int i, n = sentEmail.size() - 1; n--;) //輸入寄信人和收信人(index → value)
		{
			cin >> i >> input;
			sentEmail[i] = input;
		}

		int minIndex = nodeNum, max = 0; //題目求第一封信寄給誰能使最多人看到(max同則取index較小者)
		for (int counter, k = 1; k < sentEmail.size(); k++) //counter記錄該次dfs走訪過幾個點
		{
			if (node[k] == false) //若該點還未被走訪(若該點在先前已走訪過，則將其作為起點做dfs後的counter必定小於max，若不判斷會導致超時)
			{
				dfs(k, counter = 1); //每次dfs前將counter設為1(要算入起始點)
				if (counter > max) //因index由小到大開始dfs，故只需考慮max即可
				{
					max = counter;
					minIndex = k;
				}
			}
		}

		cout << "Case " << t << ": " << minIndex << endl;
	}
}