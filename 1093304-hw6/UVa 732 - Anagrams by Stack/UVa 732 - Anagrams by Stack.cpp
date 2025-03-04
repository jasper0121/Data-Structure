#include<iostream>
#include<stack>
using namespace std;

string input, output; //output == ���r�����Ǫ�input

void dfs(int in, int out, string process, stack<char>temp) //in == input��e��index�Bout�P�z�Bprocess == �r���ﶶ�Ǫ��L�{
{
	if (process.size() == input.size() * 4) //process���� == input + output + �C��i��o�᭱�ҥH�@�Ӫť���Ϲj == input(��output)���ת�4��
	{
		process.pop_back(); //�ҨD��process�̫�|�h�X�@�Ӫť���A�G���N�̫᪺�ť���R��
		cout << process << endl; //�L�X�ҨD
		return;
	}

	if (in < input.size())
	{
		temp.push(input[in]); //�Ninput��e���r���s�J�Ȧs
		dfs(in + 1, out, process + "i ", temp); //input��e��index + 1�Ai�N��N�r���s�J�Ȧs�A�~��]���j(i���`�� == input������)
		temp.pop(); //temp���ݪ��r���w�]�L�W�@�檺dfs�A�G�R��
	}

	if (temp.size() && temp.top() == output[out]) //�Y�Ȧs�����ťB�Y�Ȧs���ݪ��r���Moutput��eindex���r���ۦP
	{
		temp.pop(); //�N�Ȧs���ݪ��r���R��
		dfs(in, out + 1, process + "o ", temp); //output��e��index + 1�Ao�N��N�r���q�Ȧs���X�A�~��]���j(o���`�� == output������)
	}
}

int main()
{
	while (cin >> input >> output)
	{
		stack<char>temp; //�r�����Ȧs
		cout << "[\n";
		if (input.size() == output.size()) //�Y��J�M��X���r����׬ۦP
		{
			dfs(0, 0, "", temp); //�N��input�i��i�H���r�������ܦ�output�A�]dfs�`���u���j�M(�]�D�بD��ﶶ�Ǫ��Ҧ��i��L�{)
		}

		cout << "]\n";
	}

	system("pause");
}