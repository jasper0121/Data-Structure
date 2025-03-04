#include<iostream>
#include<queue>
using namespace std;

struct Register //建立struct
{
	int id, period, cost; //ID-number、週期、經過時間
	bool operator>(const Register& right)const //priority_queue中的greater重載用，否則priority_queue無法在Register形態下比大小
	{
		//在greater中的operator()裡被使用，其中的right需要是const，且operator()本身是const function，故operator>也要設為const function才能被呼叫
		return(cost == right.cost) ? id > right.id:cost > right.cost; //若cost相同則比id的大小
	}
};

int main()
{
	Register data; //要放入priority_queue裡的data
	//保存資料的型態為Register、以vector實作(若不寫亦預設為vector)、greater令top()的值最小 (若不寫則預設less (top()的值最大))
	priority_queue <Register, vector<Register>, greater<Register>> event;
	for (string keyword; cin >> keyword, keyword != "#";) //每次輸入字串，若輸入"#"則跳出
	{
		if (keyword == "Register") //若輸入Register
		{
			cin >> data.id >> data.period; //則設定ID-number和週期
			data.cost = data.period; //初始cost和period相同
			event.push(data); //將data新增至event中(過程中會將最小的值推至top()，因型態是Register故需重載operator>來新增定義如何比大小)
		}
	}

	int num;
	for (cin >> num; num--;) //輸入一個數num，輸出前num個cost最小的id(cost相同則會優先輸出id較小者)
	{
		cout << event.top().id << endl;
		data.id = event.top().id;
		data.period = event.top().period;
		data.cost = event.top().cost + data.period;
		event.push(data); //每次cost + period後再存回event
		event.pop(); //舊資料刪除	
	}

	system("pause");
}