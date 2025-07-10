#include <iostream>
#include <iomanip>
#include "class.h"

using namespace std;

int main() {
    // 创建市场
    Market market;

    // 读取股票数据
    int stock_count;
    cin >> stock_count;

    map<string, unique_ptr<User>> user_map;

    for (int i = 0; i < stock_count; i++) {
        char type;
        string id, currency;
        int num;
        int value;
        cin >> type >> id >> currency >> num >> value;

        // 创建股票 - 使用原来的stock类(现在继承自Asset)
        auto s = make_shared<stock>(type, id, currency, num, value);

        // 查找或创建用户
        if (user_map.find(id) == user_map.end()) {
            user_map[id] = make_unique<User>(id, "User_" + id);
        }

        // 添加股票到用户投资组合
        user_map[id]->addStock(s);
    }

    // 将所有用户添加到市场
    for (auto& pair : user_map) {
        market.addUser(move(pair.second));
    }

    // 读取汇率数据
    int rate_count;
    cin >> rate_count;

    Conv& conv = market.getConv();
    for (int i = 0; i < rate_count; i++) {
        string ori_cur, cur;
        double rate_value;
        cin >> ori_cur >> cur >> rate_value;
        conv.add(rate(ori_cur, cur, rate_value));
    }

    // 处理查询
    int query_count;
    cin >> query_count;

    Proc proc(market);
    double person_result = 0.0;
    double stock_result = 0.0;

    for (int i = 0; i < query_count; i++) {
        string query_type;
        cin >> query_type;

        if (query_type == "PERSON") {
            string person_id, currency;
            cin >> person_id >> currency;

            // 使用多态方式处理查询
            auto query = make_unique<PQuery>(market, person_id, currency);
            person_result = proc.run(move(query));
        }
        else if (query_type == "STOCK") {
            char stock_type;
            string currency;
            cin >> stock_type >> currency;

            // 使用多态方式处理查询
            auto query = make_unique<SQuery>(market, stock_type, currency);
            stock_result = proc.run(move(query));
        }
    }

    // 输出结果
    cout << fixed << setprecision(2) << person_result << endl;
    cout << fixed << setprecision(0)<< stock_result << endl;

    return 0;
}