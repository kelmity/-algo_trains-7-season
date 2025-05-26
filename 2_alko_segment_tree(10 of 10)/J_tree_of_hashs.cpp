#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_N = 1000001;
const long long BASE = 131;
const long long MOD = 1000000007;
long long power[MAX_N], sum_pows[MAX_N];

struct SegmentTree {
    struct Node {
        int left, right;    
        long long hash, lazy;
        Node *lc, *rc;
        
        Node(int l, int r) : left(l), right(r), hash(0), lazy(-1), lc(nullptr), rc(nullptr) {}
    };

    Node* root;

    void precompute() {
        power[0] = 1;
        for (int i = 1; i < MAX_N; ++i)
            power[i] = (__int128)power[i-1] * BASE % MOD;
        
        sum_pows[0] = 0;
        for (int i = 1; i < MAX_N; ++i)
            sum_pows[i] = ((__int128)sum_pows[i-1] * BASE + 1) % MOD;
    }

    Node* build(int l, int r, vector<int>& data) {
        Node* node = new Node(l, r);
        if (l == r) {
            node->hash = data[l] % MOD;
            return node;
        }
        int mid = (l + r) / 2;
        node->lc = build(l, mid, data);
        node->rc = build(mid+1, r, data);
        updateHash(node);
        return node;
    }

    void push(Node* node) {
        if (node->lazy != -1 && node->lc) {
            int lenL = node->lc->right - node->lc->left + 1;
            node->lc->hash = (__int128)node->lazy * sum_pows[lenL] % MOD;
            node->lc->lazy = node->lazy;

            int lenR = node->rc->right - node->rc->left + 1;
            node->rc->hash = (__int128)node->lazy * sum_pows[lenR] % MOD;
            node->rc->lazy = node->lazy;

            node->lazy = -1;
        }
    }

    void updateHash(Node* node) {
        int lenR = node->rc->right - node->rc->left + 1;
        node->hash = ((__int128)node->lc->hash * power[lenR] + node->rc->hash) % MOD;
    }

    void setRange(Node* node, int l, int r, long long val) {
        if (node->right < l || node->left > r) return;
        if (l <= node->left && node->right <= r) {
            int len = node->right - node->left + 1;
            node->hash = (__int128)val * sum_pows[len] % MOD;
            node->lazy = val;
            return;
        }
        push(node);
        setRange(node->lc, l, r, val);
        setRange(node->rc, l, r, val);
        updateHash(node);
    }

    long long getHash(Node* node, int l, int r) {
        if (node->right < l || node->left > r) return 0;
        if (l <= node->left && node->right <= r) return node->hash;
        push(node);
        
        int mid = (node->left + node->right) / 2;
        long long leftHash = getHash(node->lc, l, r);
        long long rightHash = getHash(node->rc, l, r);
        
        if (r <= mid) return leftHash;
        if (l > mid) return rightHash;
        
        int rightLen = min(r, node->rc->right) - mid;
        return ((__int128)leftHash * power[rightLen] + rightHash) % MOD;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    SegmentTree st;
    st.precompute();
    
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    
    st.root = st.build(0, n-1, arr);
    
    int q;
    cin >> q;
    string res;
    while (q--) {
        int type, a, b, k;
        cin >> type >> a >> b >> k;
        a--; b--;
        
        if (type == 0) {
            st.setRange(st.root, a, b, k);
        } else {
            int len = k;
            long long h1 = st.getHash(st.root, a, a + len - 1);
            long long h2 = st.getHash(st.root, b, b + len - 1);
            res += (h1 == h2) ? '+' : '-';
        }
    }
    
    cout << res << endl;
    return 0;
}