#include <iostream>
#include <vector>

using namespace std;

class CompCon {
private:
    vector<int> p;
    vector<int> size;
    
public:
    CompCon(int n) {
        p.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i)
            p[i] = i;
    }
    
    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    
    int conect(int x, int y) {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root)
            return 0;
        
        if (size[x_root] < size[y_root])
            swap(x_root, y_root);
        
        p[y_root] = x_root;
        size[x_root] += size[y_root];
        return size[x_root];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    
    CompCon graph(n);
    
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        x--; y--; // zero - based ind
        int new_size = graph.conect(x, y);
        if (new_size >= n) {
            cout << i + 1 << endl; // back to 1 based
            return 0;
        }
    }
    
    cout << m << endl;
    
    return 0;
}