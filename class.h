#pragma once
//��һ���˻��࣬�гֹ�����ȵȶ���˽�б������м���ϼ��ʲ��ĺ�����
//�ڶ�������������йأ������˽�б��������ػ��ʵĺ���
#include <string>

using namespace std;


class stock {
private:
	char stock_type;//��Ʊ����
	string id;
	string currency_type;//����
	int num;//�ɷ�
	int value;//�ɼ�
 static	int total;//�ϼ�
public:
	stock(char s, string i, string c, int n, int v, int t);
	double cal();//����total���������˻����ܽ��
	double self();//�����Լ��˻��Ľ��
	string name()
	{
		return id;
	}
	string currency()
	{
		return currency_type;
	}
};

class rate {
private:
	string ori_cur;//ԭ����
	string cur;//����
	double r;//����
public:
	rate(string o, string c, double r);
	double ra();
};
