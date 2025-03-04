#include<iostream>
#include<set>
using namespace std;

int main()
{
	size_t day, num_of_bills, amount, total = 0; //活動天數、帳單(抽獎券)總數、單筆帳單金額、官方支出金額
	for (multiset<int>bill; cin >> day, day; bill.clear(), total = 0) //建立帳單的multiset(1個key可以有多種val)、每次先輸入活動天數、每次帳單和total初始化
	{
		for (; day--; bill.erase(bill.begin()), bill.erase(--bill.end())) //活動期間內每天抽金額最小和最大(day順便初始化)、每次刪除該2筆帳單
		{
			for (cin >> num_of_bills; num_of_bills--;) //先輸入該天有幾筆帳單(num_of_bills順便初始化)、每次輸入單筆帳單金額並插入
			{
				cin >> amount;
				bill.insert(amount);
			}

			total += *--bill.end() - *bill.begin(); //官方總支出 == 活動期間內每天結算抽獎箱內的最大金額差(end() == 最後一個的下一個，故要記得先--)
		}

		cout << total << endl;
	}

	system("pause");
}