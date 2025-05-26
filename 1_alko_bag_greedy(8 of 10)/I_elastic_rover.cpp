#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Item {
    int v, c, p, ind;
};

int main() {
    int n, s;
    cin >> n >> s;
    
    vector<Item> items;
    for (int i = 0; i < n; ++i) {
        int v, c, p;
        cin >> v >> c >> p;
        items.push_back({v, c, p, i + 1});
    }
    
    int mx1 = 0;
    vector<int> arr;
    
    int total_v = 0;
    for (const auto& item : items) {
        total_v += item.v;
    }
    
    if (total_v <= s) {
        for (const auto& item : items) {
            mx1 += item.c;
        }
        for (const auto& item : items) {
            arr.push_back(item.ind);
        }
    } else {
        vector<int> table(s + 1, -1);
        vector<vector<int>> seq(s + 1);
        table[0] = 0;
        
        for (const auto& item : items) {
            int v = item.v;
            int c = item.c;
            int ind = item.ind;
            
            for (int j = s; j >= v; --j) {
                if (table[j - v] != -1 && table[j] < table[j - v] + c) {
                    table[j] = table[j - v] + c;
                    seq[j] = seq[j - v];
                    seq[j].push_back(ind);
                }
            }
        }
        
        mx1 = -1;
        int best_ind = 0;
        for (int j = 0; j <= s; ++j) {
            if (table[j] > mx1) {
                mx1 = table[j];
                best_ind = j;
            }
        }
        
        if (mx1 != -1) {
            arr = seq[best_ind];
        }
    }
    
    int mx2 = 0;
    vector<int> selected_b;
    
    vector<Item> items_sorted = items;
    sort(items_sorted.begin(), items_sorted.end(), [](const Item& a, const Item& b) {
        return a.p > b.p;
    });
    
    unordered_map<int, pair<int, vector<int>>> table;
    table[0] = {0, {}};
    
    for (const auto& item : items_sorted) {
        int v = item.v;
        int c = item.c;
        int p = item.p;
        int ind = item.ind;
        
        unordered_map<int, pair<int, vector<int>>> new_table;
        
        for (const auto& entry : table) {
            int vol = entry.first;
            int cost = entry.second.first;
            const vector<int>& ids = entry.second.second;
            
            if (new_table.find(vol) == new_table.end() || cost > new_table[vol].first) {
                new_table[vol] = {cost, ids};
            }
        }
        
        for (const auto& entry : table) {
            int vol = entry.first;
            int cost = entry.second.first;
            const vector<int>& ids = entry.second.second;
            
            int new_vol = vol + v;
            int new_cost = cost + c;
            vector<int> new_ids = ids;
            new_ids.push_back(ind);
            
            if (new_table.find(new_vol) == new_table.end() || new_cost > new_table[new_vol].first) {
                new_table[new_vol] = {new_cost, new_ids};
            }
        }
        
        table = move(new_table);
        
        for (const auto& entry : table) {
            int vol = entry.first;
            int cost = entry.second.first;
            const vector<int>& ids = entry.second.second;
            
            if (vol > s && (vol - s) <= p) {
                if (cost > mx2) {
                    mx2 = cost;
                    selected_b = ids;
                }
            }
        }
    }
    
    int total = 0;
    vector<int> selected;
    
    if (mx1 >= mx2) {
        total = mx1;
        selected = arr;
    } else {
        total = mx2;
        selected = selected_b;
    }
    
    vector<int> unique_selected;
    unordered_set<int> seen;
    for (int ind : selected) {
        if (seen.find(ind) == seen.end()) {
            seen.insert(ind);
            unique_selected.push_back(ind);
        }
    }
    
    cout << unique_selected.size() << " " << total << endl;
    if (!unique_selected.empty()) {
        for (size_t i = 0; i < unique_selected.size(); ++i) {
            if (i > 0) {
                cout << " ";
            }
            cout << unique_selected[i];
        }
        cout << endl;
    } else {
        cout << endl;
    }
    
    return 0;
}