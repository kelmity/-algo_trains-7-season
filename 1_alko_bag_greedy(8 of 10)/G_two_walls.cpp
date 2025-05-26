#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

pair<set<int>, vector<pair<int, vector<int>>>> pos_sm(const vector<pair<int, int>>& cur_str, int sm) {
    vector<pair<int, vector<int>>> table(sm + 1, {0, vector<int>()});
    table[0] = {1, vector<int>()};

    for (const auto& el : cur_str) {
        int value = el.first;
        int item = el.second;
        for (int j = sm; j >= value; j--) {
            if (table[j - value].first && !table[j].first) {
                table[j].first = 1;
                table[j].second = table[j - value].second;
                table[j].second.push_back(item);
            }
        }
    }

    set<int> st;
    vector<pair<int, vector<int>>> andrey;
    for (int j = 1; j < sm; j++) {
        if (table[j].first) {
            st.insert(j);
            andrey.emplace_back(j, table[j].second);
        }
    }
    return {st, andrey};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<pair<int, int>>> colors(k + 1);

    for (int i = 0; i < n; i++) {
        int l, c;
        cin >> l >> c;
        colors[c].emplace_back(l, i + 1);
    }

    vector<int> col_sums;
    int sum_val = 0;
    for (const auto& p : colors[1]) {
        sum_val += p.first;
    }
    bool possible = true;

    for (int i = 2; i <= k; i++) {
        if (colors[i].empty()) {
            possible = false;
            break;
        }

        int cur_sum = 0;
        for (const auto& p : colors[i]) {
            cur_sum += p.first;
        }
        col_sums.push_back(cur_sum);

        if (cur_sum != sum_val) {
            possible = false;
            break;
        }
    }

    if (!possible || sum_val == 0) {
        cout << "NO\n";
        return 0;
    }

    vector<set<int>> pos_sums;
    vector<vector<pair<int, vector<int>>>> ex(k + 1);

    for (int i = 1; i <= k; i++) {
        auto [st, t] = pos_sm(colors[i], sum_val);
        ex[i] = t;
        pos_sums.push_back(st);
    }

    set<int> intersec = pos_sums[0];
    for (size_t i = 1; i < pos_sums.size(); i++) {
        set<int> temp;
        set_intersection(intersec.begin(), intersec.end(),
                        pos_sums[i].begin(), pos_sums[i].end(),
                        inserter(temp, temp.begin()));
        intersec = temp;
        if (intersec.empty()) {
            cout << "NO\n";
            return 0;
        }
    }

    int wall_fst = *intersec.begin();
    vector<int> aa;

    for (int i = 1; i <= k; i++) {
        bool found = false;
        for (const auto& el : ex[i]) {
            if (el.first == wall_fst) {
                found = true;
                aa.insert(aa.end(), el.second.begin(), el.second.end());
                break;
            }
        }
        if (!found) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    sort(aa.begin(), aa.end());
    for (int el : aa) {
        cout << el << " ";
    }
    cout << endl;

    return 0;
}