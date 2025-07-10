

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>

using namespace std;

// ǰ������
class stock;
class rate;
class Portfolio;
class CurrencyConverter;

// �����ʲ��� - �̳л���
class Asset {
protected:
    string id;
    string currency_type;
    double value;

public:
    Asset(const string& i, const string& c, double v);
    virtual ~Asset() = default;

    // ���麯��
    virtual double cal() = 0;

    // �麯��
    virtual string name() const { return id; }
    virtual string currency() const { return currency_type; }
    virtual double getValue() const { return value; }

    void setValue(double v) { value = v; }
};

// ��Ʊ�� - �̳���Asset
class stock : public Asset {
private:
    char stock_type;
    int num;

public:
    static int total;

    stock(char s, const string& i, const string& c, int n, int v);

    // ��д�麯��
    double cal() override;
    double self();

    // �·���
    char st() const { return stock_type; }
    int getNum() const { return num; }
    void setNum(int n) { num = n; }
};

// ������
class rate {
private:
    string ori_cur;
    string cur;
    double r;

public:
    rate(const string& o, const string& c, double rate_val);

    double ra() const { return r; }
    string o() const { return ori_cur; }
    string c() const { return cur; }
};

// ����ת������
class Conv {
private:
    vector<rate> rates;

public:
    void add(const rate& r);
    double convert(double amount, const string& from, const string& to) const;
    bool has(const string& from, const string& to) const;
    void clear() { rates.clear(); }

    const vector<rate>& get() const { return rates; }
};

// Ͷ�������
class Port {
private:
    string owner_id;
    vector<shared_ptr<stock>> stocks;

public:
    explicit Port(const string& owner);

    void add(shared_ptr<stock> s);
    void remove(const string& stock_id);

    double total(const string& currency, const Conv& conv) const;
    vector<shared_ptr<stock>> byType(char type) const;
    shared_ptr<stock> byId(const string& id) const;

    string owner() const { return owner_id; }
    const vector<shared_ptr<stock>>& all() const { return stocks; }
    size_t size() const { return stocks.size(); }
};

// Ͷ������
class User {
private:
    string user_id;
    string name;
    unique_ptr<Port> port;

public:
    User(const string& id, const string& user_name);
    ~User() = default;

    User(const User&) = delete;
    User& operator=(const User&) = delete;
    User(User&&) = default;
    User& operator=(User&&) = default;

    void addStock(shared_ptr<stock> s);
    double total(const string& currency, const Conv& conv) const;

    string id() const { return user_id; }
    string getName() const { return name; }
    const Port* getPort() const { return port.get(); }
};

// �г���
class Market {
private:
    vector<unique_ptr<User>> users;
    Conv conv;
    map<char, double> totals;

public:
    void addUser(unique_ptr<User> user);
    User* find(const string& id);

    Conv& getConv() { return conv; }
    const Conv& getConv() const { return conv; }

    void update(char type, const string& currency);
    double get(char type) const;
    void clear() { totals.clear(); }

    double person(const string& person_id, const string& currency);
    double stock(char stock_type, const string& currency);

    const vector<unique_ptr<User>>& all() const { return users; }
};

// ��ѯ���� - �̳л���
class Query {
protected:
    Market& market;

public:
    explicit Query(Market& m);
    virtual ~Query() = default;

    // ���麯��
    virtual double exec() = 0;
    virtual string type() const = 0;
};

// ���˲�ѯ�� - �̳���Query
class PQuery : public Query {
private:
    string person_id;
    string currency;

public:
    PQuery(Market& m, const string& id, const string& cur);

    // ��д�麯��
    double exec() override;
    string type() const override { return "PERSON"; }

    string getId() const { return person_id; }
    string getCur() const { return currency; }
};

// ��Ʊ��ѯ�� - �̳���Query  
class SQuery : public Query {
private:
    char stock_type;
    string currency;

public:
    SQuery(Market& m, char t, const string& cur);

    // ��д�麯��
    double exec() override;
    string type() const override { return "STOCK"; }

    char getType() const { return stock_type; }
    string getCur() const { return currency; }
};

// ��ѯ��������
class Proc {
private:
    Market& market;

public:
    explicit Proc(Market& m);

    double person(const string& person_id, const string& currency);
    double stock(char stock_type, const string& currency);

    // ʹ�ö�̬�����ѯ
    double run(unique_ptr<Query> query);
    vector<double> batch(const vector<string>& commands);
};
