#include<iostream>
#include<algorithm> //�n�Ψ�sort
#include<vector>
#include<map>
using namespace std;

int main()
{
	int num, max = 0, total = 0; //�ǥͤH�ơB�̼����Ҫ��H�ơB�̼����Ҫ��`�H��(�Y���ۦP�ƶq���̼����ҫh�ƶq�[�`)
	map<vector<int>, int>student; //�ҵ{�զX�M��H�ƪ�map
	for (vector<int>course(5); cin >> num, num; student.clear(), max = total = 0) //�Ҹ��զX�B�C����J�ǥͤH�ơB�C��max�Mtotal��l��
	{
		for (int s = 0; s < num; s++) //�ǥͤH��
		{
			for (int c = 0; c < 5; c++) //��J5�ؽҸ�
			{
				cin >> course[c];
			}

			sort(course.begin(), course.end()); //�ƧǡA�w�]�Ѥp�ƨ�j
			if (student.count(course)) //�Y�ӽҵ{�զX�w�s�b
			{
				student[course]++; //�h�H�� + 1
			}
			else
			{
				student.insert({ course,1 }); //�_�h�s�W�@�ӽҵ{�զX
			}
		}

		for (map<vector<int>, int>::iterator it = student.begin(); it != student.end(); it++)
		{
			if (max < it->second) //�Y���H�Ƨ�h���ҵ{�զX
			{
				max = total = it->second; //�h�����ӽҪ��H��
			}
			else if (max == it->second) //�Y���H�ƬۦP����
			{
				total += it->second; //�h�N��H�ƥ[�`
			}
		}

		cout << total << endl;
	}

	system("pause");
}