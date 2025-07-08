#include "class.h"
#include <string>

using namespace std;

int stock::total = 0;


stock::stock(char s, string i, string c, int n, int v):stock_type(s), id(i), currency_type(c), num(n), value(v){}

double stock:: cal()
{
	return total;
}

double stock::self()
{
	int a = num * value;//自己账户的余额

	return a;
}

rate::rate(string o, string c, double r) :ori_cur(o), cur(c), r(r) {}

double rate::ra()
{
	return r;
}