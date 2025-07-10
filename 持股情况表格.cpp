#include <iostream>
#include <iomanip>
#include "class.h"

using namespace std;

int main() {
    // �����г�
    Market market;

    // ��ȡ��Ʊ����
    int stock_count;
    cin >> stock_count;

    map<string, unique_ptr<User>> user_map;

    for (int i = 0; i < stock_count; i++) {
        char type;
        string id, currency;
        int num;
        int value;
        cin >> type >> id >> currency >> num >> value;

        // ������Ʊ - ʹ��ԭ����stock��(���ڼ̳���Asset)
        auto s = make_shared<stock>(type, id, currency, num, value);

        // ���һ򴴽��û�
        if (user_map.find(id) == user_map.end()) {
            user_map[id] = make_unique<User>(id, "User_" + id);
        }

        // ��ӹ�Ʊ���û�Ͷ�����
        user_map[id]->addStock(s);
    }

    // �������û���ӵ��г�
    for (auto& pair : user_map) {
        market.addUser(move(pair.second));
    }

    // ��ȡ��������
    int rate_count;
    cin >> rate_count;

    Conv& conv = market.getConv();
    for (int i = 0; i < rate_count; i++) {
        string ori_cur, cur;
        double rate_value;
        cin >> ori_cur >> cur >> rate_value;
        conv.add(rate(ori_cur, cur, rate_value));
    }

    // �����ѯ
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

            // ʹ�ö�̬��ʽ�����ѯ
            auto query = make_unique<PQuery>(market, person_id, currency);
            person_result = proc.run(move(query));
        }
        else if (query_type == "STOCK") {
            char stock_type;
            string currency;
            cin >> stock_type >> currency;

            // ʹ�ö�̬��ʽ�����ѯ
            auto query = make_unique<SQuery>(market, stock_type, currency);
            stock_result = proc.run(move(query));
        }
    }

    // ������
    cout << fixed << setprecision(2) << person_result << endl;
    cout << fixed << setprecision(0)<< stock_result << endl;

    return 0;
}