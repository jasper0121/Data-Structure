#include<iostream>
#include<iomanip>
#include<string>
#include<map>
using namespace::std;

int main()
{
	int testCase, total = 0; //幾組測資
	string treeName; //樹的種類
	cin >> testCase;
	cin.ignore(); //清除cin的緩衝區
	getline(cin, treeName); //輸入enter當分隔用
	map<string, double>species; //存樹的名稱及樹的輸入次數
	for (int k = 0; k < testCase; species.clear(), total = 0, k++) //進下組測資前將species和total初始化
	{
		if (k != 0)
		{
			cout << endl;
		}

		for (; getline(cin, treeName), treeName != ""; total++) //每次先輸入，若輸入不是只有enter
		{
			if (species.count(treeName)) //若map中已經有輸入的樹名(count == 回傳key在map中的出現次數。因key唯一，故回傳最大為1)
			{
				species[treeName]++; //則其value + 1表示該樹的輸入次數
			}
			else
			{
				species.insert({ treeName,1 }); //否則插入，包含樹名和該樹的輸入次數
			}
		}

		for (map<string, double>::iterator it = species.begin(); it != species.end(); it++) //輸出當前的樹名輸入次數佔總輸入的百分比
		{
			//fixed == 使接下來的setprecision只作用在小數點後、setprecision == 取4位數，最後一位自動四捨五入(若前沒有fixed則包含整數部分)
			cout << it->first << " " << fixed << setprecision(4) << it->second / total * 100 << endl;
		}
	}

	system("pause");
}