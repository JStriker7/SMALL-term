#include <iostream>
#include "class.h"
#include <vector>
#include <iomanip> 
#include <cmath>
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
	double result = 0;
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
						 result = floor(account[i].self() * 100) / 100.0;
						
					}
					else
					{
						//�ȼ����ܽ�����������ת��Ϊ�ո������cur����type���͵��ܽ��
						double a = account[i].self();
						//�ؼ�������ô�ҵ���Ӧ����
						for (int j = 0; j < rates.size(); j++)
						{
							if (rates[j].o() == account[i].currency() && rates[j].c() == cur_type)
							{
								double re = a * rates[j].ra();
								 result= floor(re * 100) / 100.0;
								
							}
						}
					}
				}
				
			}
		}
		else if(q_type=="STOCK")//��μ���total//����account������в���char���͵Ĺɣ���������㣬����в���type���͵Ľ��ģ���ת���ɶ�Ӧ���͵ı���
		{
			char a;
			string type;
			cin >> a >>type;
			for (int i = 0; i < account.size(); i++)
			{
				if (account[i].st() == a)
				{
					if (account[i].currency() == type)
					{
						stock::total += account[i].self();

					}
					else
					{
						for (int j = 0; j < rates.size(); j++)
						{
							if (rates[j].o() == type && rates[j].c() == account[i].currency())
							{
								double re = account[i].self() / rates[j].ra();
								stock::total += re;
								
							}
							
						}
					}
				}
			}

		}
	}
	cout << fixed << setprecision(2) << result << endl;
	cout << fixed << setprecision(2) << stock::total << endl;
}