#include<iostream>
#include<algorithm> //要用到sort
#include<vector>
#include<map>
using namespace std;

int main()
{
	int num, max = 0, total = 0; //學生人數、最熱門課的人數、最熱門課的總人數(若有相同數量的最熱門課則數量加總)
	map<vector<int>, int>student; //課程組合和其人數的map
	for (vector<int>course(5); cin >> num, num; student.clear(), max = total = 0) //課號組合、每次輸入學生人數、每次max和total初始化
	{
		for (int s = 0; s < num; s++) //學生人數
		{
			for (int c = 0; c < 5; c++) //輸入5種課號
			{
				cin >> course[c];
			}

			sort(course.begin(), course.end()); //排序，預設由小排到大
			if (student.count(course)) //若該課程組合已存在
			{
				student[course]++; //則人數 + 1
			}
			else
			{
				student.insert({ course,1 }); //否則新增一個課程組合
			}
		}

		for (map<vector<int>, int>::iterator it = student.begin(); it != student.end(); it++)
		{
			if (max < it->second) //若找到人數更多的課程組合
			{
				max = total = it->second; //則紀錄該課的人數
			}
			else if (max == it->second) //若找到人數相同的課
			{
				total += it->second; //則將其人數加總
			}
		}

		cout << total << endl;
	}

	system("pause");
}