#include<iostream>
#include<queue>
using namespace std;

struct Register //�إ�struct
{
	int id, period, cost; //ID-number�B�g���B�g�L�ɶ�
	bool operator>(const Register& right)const //priority_queue����greater�����ΡA�_�hpriority_queue�L�k�bRegister�κA�U��j�p
	{
		//�bgreater����operator()�̳Q�ϥΡA�䤤��right�ݭn�Oconst�A�Boperator()�����Oconst function�A�Goperator>�]�n�]��const function�~��Q�I�s
		return(cost == right.cost) ? id > right.id:cost > right.cost; //�Ycost�ۦP�h��id���j�p
	}
};

int main()
{
	Register data; //�n��Jpriority_queue�̪�data
	//�O�s��ƪ����A��Register�B�Hvector��@(�Y���g��w�]��vector)�Bgreater�Otop()���ȳ̤p (�Y���g�h�w�]less (top()���ȳ̤j))
	priority_queue <Register, vector<Register>, greater<Register>> event;
	for (string keyword; cin >> keyword, keyword != "#";) //�C����J�r��A�Y��J"#"�h���X
	{
		if (keyword == "Register") //�Y��JRegister
		{
			cin >> data.id >> data.period; //�h�]�wID-number�M�g��
			data.cost = data.period; //��lcost�Mperiod�ۦP
			event.push(data); //�Ndata�s�W��event��(�L�{���|�N�̤p���ȱ���top()�A�]���A�ORegister�G�ݭ���operator>�ӷs�W�w�q�p���j�p)
		}
	}

	int num;
	for (cin >> num; num--;) //��J�@�Ӽ�num�A��X�enum��cost�̤p��id(cost�ۦP�h�|�u����Xid���p��)
	{
		cout << event.top().id << endl;
		data.id = event.top().id;
		data.period = event.top().period;
		data.cost = event.top().cost + data.period;
		event.push(data); //�C��cost + period��A�s�^event
		event.pop(); //�¸�ƧR��	
	}

	system("pause");
}