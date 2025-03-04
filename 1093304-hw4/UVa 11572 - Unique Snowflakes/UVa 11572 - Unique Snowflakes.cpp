#include<iostream>
#include<set>
using namespace std;

int main()
{
	int testCase, num, first = 0, len = 0, max = 0; //幾組測資、雪花數量、數列的起始位置、當前數列長度、數列的最大長度(此數列內數字不重複且按輸入順序)
	int* type = new int[1000000]; //雪花種類(題目說種類不會超過100萬種)
	set<int> snowflakes; //快速查詢有無重複雪花種類用
	for (cin >> testCase; testCase--; snowflakes.clear(), first = len = max = 0) //輸入有幾組測資、每次first,len,max初始化
	{
		cin >> num; //輸入有多少雪花
		for (int a = 0; a < num; a++) //輸入雪花種類
		{
			cin >> type[a];
		}

		for (int cur = 0; cur < num; cur++) //找出數列的最大長度
		{
			for (; snowflakes.count(type[cur]); first++, len--) //若要插入的值已存在當前數列範圍中、每次起始位置會往後，相對地長度也會減少
			{
				snowflakes.erase(type[first]); //則一直刪除到該值不在數列範圍內為止
			}

			snowflakes.insert(type[cur]);
			if (++len > max) //每次插入新的數後長度會 + 1，若當前的數列長度為最大
			{
				max = len; //則將長度記錄下來
			}
		}

		cout << max << endl; //最後輸出數列的最大長度
	}

	delete[] type; //刪除動態陣列
	system("pause");
}