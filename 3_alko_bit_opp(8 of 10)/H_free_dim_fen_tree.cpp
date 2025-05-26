#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
private:
    int n;
    vector<vector<vector<long long>>> tree;

    void oneBased(int& x, int& y, int& z) {
        x++;
        y++;
        z++;
    }

public:
    FenwickTree(int size) : n(size) {
        tree.resize(n + 1, vector<vector<long long>>(n + 1, vector<long long>(n + 1, 0)));
    }

    void update(int x, int y, int z, long long delta) {
        oneBased(x, y, z);
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= n; j += j & -j) {
                for (int k = z; k <= n; k += k & -k) {
                    tree[i][j][k] += delta;
                }
            }
        }
    }

    long long query(int x, int y, int z) {
        oneBased(x, y, z);
        long long res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                for (int k = z; k > 0; k -= k & -k) {
                    res += tree[i][j][k];
                }
            }
        }
        return res;
    }

    long long rangeRequest(int x1, int y1, int z1, int x2, int y2, int z2) {
        return query(x2, y2, z2) - query(x1 - 1, y2, z2) - query(x2, y1 - 1, z2) - query(x2, y2, z1 - 1) + query(x1 - 1, y1 - 1, z2) + query(x1 - 1, y2, z1 - 1) + query(x2, y1 - 1, z1 - 1) - query(x1 - 1, y1 - 1, z1 - 1);
        //             000-0               -100 - 1             0-10 - 2                     00-1 - 3                  -1-10 - 4                  -10-1 - 5                       0-1-1 - 6                   -1-1-1 - 7                
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    FenwickTree ft(n);
    vector<vector<vector<long long>>> arr(n, vector<vector<long long>>(n, vector<long long>(n, 0)));

    int m;
    while (true) {
        cin >> m;
        if (m == 1) {
            int x, y, z, k;
            cin >> x >> y >> z >> k;
            arr[x][y][z] += k;
            ft.update(x, y, z, k);
        } else if (m == 2) { // Запрос суммы
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << ft.rangeRequest(x1, y1, z1, x2, y2, z2) << '\n';
        } else if (m == 3) { // Выход
            break;
        }
    }

    return 0;
}