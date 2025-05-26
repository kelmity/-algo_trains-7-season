#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
private:
    vector<long long> tree;

    int lsb(int x) {
        return x & -x;
    }
    
public:
    FenwickTree(int size) {
        tree.resize(size + 1, 0);
    }

    void update(int ind, long long dif) {
        ind++;
        while (ind < tree.size()) {
            tree[ind] += dif;
            ind += lsb(ind);
        }
    }

    long long query(int ind) {
        ind++;
        long long sum = 0;
        while (ind > 0) {
            sum += tree[ind];
            ind -= lsb(ind);
        }
        return sum;
    }

    long long rangeRequest(int left, int right) {
        return query(right) - query(left - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    FenwickTree ft(n);
    vector<long long> arr(n + 1, 0);

    while (k--) {
        char type;
        cin >> type;

        if (type == 'A') {
            int i;
            long long x;
            cin >> i >> x;
            long long dif = x - arr[i];
            arr[i] = x;
            ft.update(i - 1, dif);
        } else if (type == 'Q') {
            int l, r;
            cin >> l >> r;
            cout << ft.rangeRequest(l - 1, r - 1) << '\n';
        }
    }

    return 0;
}