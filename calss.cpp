#include "class.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>

// Asset基类实现
Asset::Asset(const string& i, const string& c, double v)
    : id(i), currency_type(c), value(v) {
}

// stock类实现 - 继承自Asset
int stock::total = 0;

stock::stock(char s, const string& i, const string& c, int n, int v)
    : Asset(i, c, v), stock_type(s), num(n) {
}

double stock::cal() {
    return total;
}

double stock::self() {
    return num * value;
}

// rate类实现
rate::rate(const string& o, const string& c, double rate_val)
    : ori_cur(o), cur(c), r(rate_val) {
}

// Conv类实现
void Conv::add(const rate& r) {
    rates.push_back(r);
}

double Conv::convert(double amount, const string& from, const string& to) const {
    if (from == to) {
        return amount;
    }

    // 直接转换
    for (const auto& rate_obj : rates) {
        if (rate_obj.o() == from && rate_obj.c() == to) {
            return amount * rate_obj.ra();
        }
    }

    // 反向转换
    for (const auto& rate_obj : rates) {
        if (rate_obj.o() == to && rate_obj.c() == from) {
            return amount / rate_obj.ra();
        }
    }

    return amount;
}

bool Conv::has(const string& from, const string& to) const {
    if (from == to) return true;

    for (const auto& rate_obj : rates) {
        if ((rate_obj.o() == from && rate_obj.c() == to) ||
            (rate_obj.o() == to && rate_obj.c() == from)) {
            return true;
        }
    }
    return false;
}

// Port类实现
Port::Port(const string& owner) : owner_id(owner) {}

void Port::add(shared_ptr<stock> s) {
    if (s) {
        stocks.push_back(s);
    }
}

void Port::remove(const string& stock_id) {
    stocks.erase(
        remove_if(stocks.begin(), stocks.end(),
            [&stock_id](const shared_ptr<stock>& s) {
                return s->name() == stock_id;
            }),
        stocks.end());
}

double Port::total(const string& currency, const Conv& conv) const {
    double result = 0.0;
    for (const auto& s : stocks) {
        double stock_value = s->self();
        double converted_value = conv.convert(stock_value, s->currency(), currency);
        result += converted_value;
    }
    return floor(result * 100) / 100.0;
}

vector<shared_ptr<stock>> Port::byType(char type) const {
    vector<shared_ptr<stock>> result;
    for (const auto& s : stocks) {
        if (s->st() == type) {
            result.push_back(s);
        }
    }
    return result;
}

shared_ptr<stock> Port::byId(const string& id) const {
    for (const auto& s : stocks) {
        if (s->name() == id) {
            return s;
        }
    }
    return nullptr;
}

// User类实现
User::User(const string& id, const string& user_name)
    : user_id(id), name(user_name), port(make_unique<Port>(id)) {
}

void User::addStock(shared_ptr<stock> s) {
    if (port && s) {
        port->add(s);
    }
}

double User::total(const string& currency, const Conv& conv) const {
    if (port) {
        return port->total(currency, conv);
    }
    return 0.0;
}

// Market类实现
void Market::addUser(unique_ptr<User> user) {
    if (user) {
        users.push_back(move(user));
    }
}

User* Market::find(const string& id) {
    for (auto& user : users) {
        if (user->id() == id) {
            return user.get();
        }
    }
    return nullptr;
}

void Market::update(char type, const string& currency) {
    double result = 0.0;

    for (const auto& user : users) {
        const Port* port = user->getPort();
        if (port) {
            auto stocks_of_type = port->byType(type);
            for (const auto& s : stocks_of_type) {
                double stock_value = s->self();
                double converted_value = conv.convert(stock_value, s->currency(), currency);
                result += converted_value;
            }
        }
    }

    totals[type] = floor(result * 100) / 100.0;
}

double Market::get(char type) const {
    auto it = totals.find(type);
    return (it != totals.end()) ? it->second : 0.0;
}

double Market::person(const string& person_id, const string& currency) {
    User* user = find(person_id);
    if (user) {
        return user->total(currency, conv);
    }
    return 0.0;
}

double Market::stock(char stock_type, const string& currency) {
    update(stock_type, currency);
    return get(stock_type);
}

// Query基类实现
Query::Query(Market& m) : market(m) {}

// PQuery类实现 - 继承自Query
PQuery::PQuery(Market& m, const string& id, const string& cur)
    : Query(m), person_id(id), currency(cur) {
}

double PQuery::exec() {
    return market.person(person_id, currency);
}

// SQuery类实现 - 继承自Query
SQuery::SQuery(Market& m, char t, const string& cur)
    : Query(m), stock_type(t), currency(cur) {
}

double SQuery::exec() {
    return market.stock(stock_type, currency);
}

// Proc类实现
Proc::Proc(Market& m) : market(m) {}

double Proc::person(const string& person_id, const string& currency) {
    return market.person(person_id, currency);
}

double Proc::stock(char stock_type, const string& currency) {
    return market.stock(stock_type, currency);
}

double Proc::run(unique_ptr<Query> query) {
    if (query) {
        return query->exec();
    }
    return 0.0;
}

vector<double> Proc::batch(const vector<string>& commands) {
    vector<double> results;

    for (const string& command : commands) {
        istringstream iss(command);
        string query_type;
        iss >> query_type;

        if (query_type == "PERSON") {
            string person_id, currency;
            iss >> person_id >> currency;
            auto query = make_unique<PQuery>(market, person_id, currency);
            results.push_back(run(move(query)));
        }
        else if (query_type == "STOCK") {
            char stock_type;
            string currency;
            iss >> stock_type >> currency;
            auto query = make_unique<SQuery>(market, stock_type, currency);
            results.push_back(run(move(query)));
        }
    }

    return results;
}