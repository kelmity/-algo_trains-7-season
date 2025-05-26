#include "bits-stdc++.h"

using namespace std;

struct Node {
    long long sum;
    long long sum_sq;
    Node() : sum(0), sum_sq(0) {
    };
    Node(long long s, long long sq) : sum(s), sum_sq(sq) {
    };
};

class SegmentTree {
public:
    SegmentTree(int n) {
        size = 1;
        while (size < n) {
            size <<= 1;
        }
        tree.resize(2 * size, Node(0, 0));
    }
    void build(const vector<int>& data, int n) {
        for (int i = 0; i < n; ++i) {
            tree[size + 1] = Node(data[i], static_cast<long long>(data[i]) * data[i]);
        }
        for (int i = size - 1; i > 0; --i) {
            tree[i].sum = tree[2 * i].sum + tree[2 * i + 1].sum;
            tree[i].sum_sq = tree[2 * i].sum_sq + tree[2 * i + 1].sum_sq;
        }
    }
    void update(int pos, int val) {
        pos += size;
        tree[pos] = Node(val, static_cast<long long>(val) * val);
        for (pos >>= 1; pos >= 1; pos >>= 1) {
            tree[pos].sum = tree[2 * pos].sum + tree[2 * pos + 1].sum;
            tree[pos].sum_sq = tree[2 * pos].sum_sq + tree[2 * pos + 1].sum_sq;
        }
    }
    Node query(int l, int r) {
        l += size;
        r += size;
        Node left, right;
        while (l <= r) {
            if (l % 2 == 1) {
                left.sum += tree[l].sum;
                left.sum_sq += tree[l].sum_sq;
                ++l;
            }
            if (r % 2 == 0) {
                right.sum += tree[r].sum;
                right.sum_sq += tree[r].sum_sq;
                --r;
            }
            l >>= 1;
            r >>= 1;
        }
        //cout<< right.sum << " " <<  left.sum << " " <<  right.sum_sq << " " << left.sum_sq << '\n';
        return Node(left.sum + right.sum, left.sum_sq + right.sum_sq);
    }

private:
    vector<Node> tree;
    int size;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin>> n >> q;
    int m = n + q;
    int size_st = 1;
    while (size_st < m) {
        size_st <<= 1;
    }

    vector<int> data(size_st, 0);
    for (int i = 0; i < n; ++i) {
        cin>> data[i];
    }
    SegmentTree st(size_st);
    st.build(data, size_st);

    int current_size = n;

    cout<< fixed << setprecision(7);

    for (int i = 0; i < q; ++i) {
        int type;
        cin>> type;
        if (type == 1) {
            int k;
            cin>> k;
            int l = current_size - k;
            int r = current_size - 1;
            Node res = st.query(l, r);
            double sum = res.sum;
            double sum_sq = res.sum_sq;
            double mean = sum / k;
            double variance = (sum_sq - sum * mean) / k;
            double std_dev = sqrt(variance);
            cout<< std_dev << '\n';
        } else {
            int x;
            cin>> x;
            st.update(current_size, x);
            ++current_size;
        }
    }
    return 0;
}
