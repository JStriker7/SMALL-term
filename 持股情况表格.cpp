#include <iostream>
#include "class.h"
#include <vector>
using namespace std;

int main()
{
	char type;
	string id;
	string cur_type;
	int num;
	int value;
	string ori_cur, cur;
	double r;
	vector<stock> account;
	vector<rate> rates;
	int a, b, c;
	cin >> a;
	while (a--)
	{
		cin >> type >> id >> cur_type >> num >> value;
		account.emplace_back(type, id, cur_type, num, value);
	}
	cin >> b;
	while (b--)
	{
		cin >> ori_cur >> cur >> r;
		rates.emplace_back(ori_cur, cur, r);

	}
	cin >> c;
	string q_type;
	while (c--)
	{
		cin >> q_type;
		if (q_type == "PERSON")
		{
			string id, cur_type;
			cin >> id >> cur_type;
			for (int i = 0; i < account.size(); i++)
			{
				if (account[i].name() == id)
				{
					if (cur_type == account[i].currency())
					{
						cout << account[i].self() << endl;
					}
					else
					{
						//先计算总金额，再利用利率转换为刚刚输入的cur——type类型的总金额
						double a = account[i].self();
						//关键点在怎么找到对应利率

					}
				}
				
			}
		}
		else if(q_type=="STOCK")//如何计算total//遍历account，如果有不是char类型的股，不加入计算，如果有不是type类型的金额的，先转换成对应类型的币种
		{
			char a;
			string type;
			cin >> a >>type;
			

		}
	}

}