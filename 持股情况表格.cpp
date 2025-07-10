#include <iostream>
#include "class.h"
#include <vector>
#include <iomanip> 
#include <cmath>
using namespace std;

void test_sample_case() {
	cout << "\n=== TDD测试开始 ===" << endl;
	cout << "测试用例：样例数据测试" << endl;

	// 重置静态变量
	stock::total = 0;

	// 创建测试数据
	vector<stock> account;
	vector<rate> rates;

	// 添加股票数据
	account.emplace_back('B', "WangWu", "CNY", 12, 25);
	account.emplace_back('B', "ZhaoLiu", "JPY", 2200, 100);

	// 添加汇率数据
	rates.emplace_back("CNY", "JPY", 22.0);
	rates.emplace_back("CNY", "USD", 0.1376);

	double person_result = 0.0;
	double stock_result = 0.0;

	// 执行PERSON查询：WangWu USD
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

	// 执行STOCK查询：B CNY
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

	// 输出测试结果
	cout << "期望结果：41.28, 10300.00" << endl;
	cout << "实际结果：" << fixed << setprecision(2) << person_result << ", " << stock_result << endl;

	// 验证结果
	bool person_ok = abs(person_result - 41.28) < 0.01;
	bool stock_ok = abs(stock_result - 10300.0) < 0.01;

	if (person_ok && stock_ok) {
		cout << "? 测试通过！" << endl;
	}
	else {
		cout << "? 测试失败！" << endl;
	}
	cout << "=== TDD测试结束 ===" << endl;
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
						//先计算总金额，再利用利率转换为刚刚输入的cur——type类型的总金额
						double a = account[i].self();
						//关键点在怎么找到对应利率
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
		else if(q_type=="STOCK")//如何计算total//遍历account，如果有不是char类型的股，不加入计算，如果有不是type类型的金额的，先转换成对应类型的币种
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
	cout << "选择运行模式：" << endl;
	cout << "1. 运行TDD测试" << endl;
	cout << "2. 运行原始程序" << endl;
	cout << "输入选择 (1或2): ";

	int choice;
	cin >> choice;

	if (choice == 1) {
		test_sample_case();
	}
	else {
		cout << "请输入数据：" << endl;
		run_original();
	}

	return 0;
}