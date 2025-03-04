#include<iostream>
#include<vector>
#include<set>
using namespace std;

int main()
{
	int testCase, bf, sg, sb, atk; //幾組測資、戰場數(battlefields)、綠軍、藍軍，攻擊力
	multiset<int, greater<int>>greenArmy, blueArmy; //存雙方軍力(原預設set的樹是左下begin()最小，右下--end()最大，此加greater使之反轉)
	cin >> testCase;
	for (int k = 0; k < testCase; greenArmy.clear(), blueArmy.clear(), k++)
	{
		if (k != 0) //一開始不要換行
		{
			cout << endl;
		}

		//戰力配置-----------------------------------------------------------------------------------------------------------
		cin >> bf >> sg >> sb; //輸入戰場數、綠軍人數、藍軍人數
		while (sg--) //輸入綠軍的攻擊力組成(順便使sg初始化)
		{
			cin >> atk;
			greenArmy.insert(atk);
		}

		while (sb--) //輸入藍軍的攻擊力組成(順便使sb初始化)
		{
			cin >> atk;
			blueArmy.insert(atk);
		}

		//戰鬥----------------------------------------------------------------------------------------------------------------
		for (vector<int>battle; greenArmy.size() != 0 && blueArmy.size() != 0; battle.clear()) //設立戰場、若雙方都還有剩餘戰力
		{
			//每次雙方對戰，持續bf個回合，若有任何一方軍力為空則戰鬥提早結束(battle的size會比bf少)
			for (int i = 0; i < bf && !(greenArmy.empty() || blueArmy.empty()); i++)
			{
				battle.insert(battle.end(), *greenArmy.begin() - *blueArmy.begin()); //戰力相減並存入battle中
				greenArmy.erase(greenArmy.begin());
				blueArmy.erase(blueArmy.begin());
			}

			for (int i = 0; i < battle.size(); i++)
			{
				if (battle[i] > 0) //若battle[i]的值為正，則綠軍贏
				{
					greenArmy.insert(battle[i]);
				}
				else if (battle[i] < 0) //若battle[i]的值為正，則藍軍贏
				{
					blueArmy.insert(-battle[i]);
				}
			}
		}

		//勝負----------------------------------------------------------------------------------------------------------------
		if (greenArmy.size() != 0) //若綠軍有剩餘
		{
			cout << "green wins\n";
			for (multiset<int>::iterator it = greenArmy.begin(); it != greenArmy.end(); it++) //印出剩餘戰力
			{
				cout << *it << endl;
			}
		}
		else if (blueArmy.size() != 0) //若藍軍有剩餘
		{
			cout << "blue wins\n";
			for (multiset<int>::iterator it = blueArmy.begin(); it != blueArmy.end(); it++) //印出剩餘戰力
			{
				cout << *it << endl;
			}
		}
		else
		{
			cout << "green and blue died\n";
		}
	}

	system("pause");
}