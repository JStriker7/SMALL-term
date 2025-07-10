#include <iostream>
#include "class.h"
#include <vector>
#include <iomanip> 
#include <cmath>
using namespace std;

void test_sample_case() {
	cout << "\n=== TDD���Կ�ʼ ===" << endl;
	cout << "�����������������ݲ���" << endl;

	// ���þ�̬����
	stock::total = 0;

	// ������������
	vector<stock> account;
	vector<rate> rates;

	// ��ӹ�Ʊ����
	account.emplace_back('B', "WangWu", "CNY", 12, 25);
	account.emplace_back('B', "ZhaoLiu", "JPY", 2200, 100);

	// ��ӻ�������
	rates.emplace_back("CNY", "JPY", 22.0);
	rates.emplace_back("CNY", "USD", 0.1376);

	double person_result = 0.0;
	double stock_result = 0.0;

	// ִ��PERSON��ѯ��WangWu USD
	for (int i = 0; i < account.size(); i++) {
		if (account[i].name() == "WangWu") {
			if ("USD" != account[i].currency()) {
				double a = account[i].self();
				for (int j = 0; j < rates.size(); j++) {
					if (rates[j].o() == account[i].currency() && rates[j].c() == "USD") {
						double re = a * rates[j].ra();
						person_result = floor(re * 100) / 100.0;
					}
				}
			}
		}
	}

	// ִ��STOCK��ѯ��B CNY
	for (int i = 0; i < account.size(); i++) {
		if (account[i].st() == 'B') {
			if (account[i].currency() == "CNY") {
				stock::total += account[i].self();
			}
			else {
				for (int j = 0; j < rates.size(); j++) {
					if (rates[j].o() == "CNY" && rates[j].c() == account[i].currency()) {
						double re = account[i].self() / rates[j].ra();
						stock::total += re;
					}
				}
			}
		}
	}
	stock_result = floor(stock::total * 100) / 100.0;

	// ������Խ��
	cout << "���������41.28, 10300.00" << endl;
	cout << "ʵ�ʽ����" << fixed << setprecision(2) << person_result << ", " << stock_result << endl;

	// ��֤���
	bool person_ok = abs(person_result - 41.28) < 0.01;
	bool stock_ok = abs(stock_result - 10300.0) < 0.01;

	if (person_ok && stock_ok) {
		cout << "? ����ͨ����" << endl;
	}
	else {
		cout << "? ����ʧ�ܣ�" << endl;
	}
	cout << "=== TDD���Խ��� ===" << endl;
}

void run_original()
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

int main()
{
	cout << "ѡ������ģʽ��" << endl;
	cout << "1. ����TDD����" << endl;
	cout << "2. ����ԭʼ����" << endl;
	cout << "����ѡ�� (1��2): ";

	int choice;
	cin >> choice;

	if (choice == 1) {
		test_sample_case();
	}
	else {
		cout << "���������ݣ�" << endl;
		run_original();
	}

	return 0;
}