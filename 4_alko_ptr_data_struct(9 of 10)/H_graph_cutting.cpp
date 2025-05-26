#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Operation {
    bool is_cut;
    int u;
    int v;
};

class CompCon {
private:
    vector<int> p;
    vector<int> size;
    
public:
    CompCon(int n) {
        p.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; ++i) {
            p[i] = i;
        }
    }
    
    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    
    void connect(int x, int y) {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root) {
            return;
        }
        
        if (size[x_root] < size[y_root]) {
            swap(x_root, y_root);
        }
        
        p[y_root] = x_root;
        size[x_root] += size[y_root];
    }
    
    bool check(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
    }
    
    vector<Operation> ops;
    for (int i = 0; i < k; ++i) {
        string cmd;
        int u, v;
        cin >> cmd >> u >> v;
        ops.push_back({cmd == "cut", u, v});
    }
    
    CompCon dsu(n);
    vector<string> res;
    
    for (auto it = ops.rbegin(); it != ops.rend(); ++it) {
        if (it -> is_cut) {
            dsu.connect(it -> u, it -> v);
        } else {
            res.push_back(dsu.check(it -> u, it -> v) ? "YES" : "NO");
        }
    }
    
    reverse(res.begin(), res.end());
    for (auto s : res) {
        cout << s << endl;
    }
    
    return 0;
}