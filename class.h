#pragma once
//有一个账户类，有持股情况等等多种私有变量，有计算合计资产的函数，
//第二个类是与汇率有关，有相关私有变量，返回汇率的函数
#include <string>

using namespace std;


class stock {
private:
	char stock_type;//股票类型
	string id;
	string currency_type;//币种
	int num;//股份
	int value;//股价

public:
	static	int total;//合计
	stock(char s, string i, string c, int n, int v);
	double cal();//返回total，即所有账户的总金额
	double self();//返回自己账户的金额
	string name()
	{
		return id;
	}
	string currency()
	{
		return currency_type;
	}
	char st()
	{
		return stock_type;
	}
	
};

class rate {
private:
	string ori_cur;//原币种
	string cur;//币种
	double r;//汇率
public:
	rate(string o, string c, double r);
	double ra();
	string o()
	{
		return ori_cur;
	}
	string c()
	{
		return  cur;
	}
};
