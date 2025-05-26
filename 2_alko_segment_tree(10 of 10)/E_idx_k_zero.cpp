#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    int count;
    int l, r;

    Node(int l1, int r1): l(l1), r(r1), value(0), count(0), left(nullptr), right(nullptr) {}
    
};

const int INF = INT_MIN;


Node* build(int l, int r, const vector<int>& arr) {
    Node* node = new Node(l, r);
    if (l == r) {
        node->count = (arr[l] == 0) ? 1 : 0;
        return node;
    }
    int mid = (l + r) / 2;
    node->left = build(l, mid, arr);
    node->right = build(mid + 1, r, arr);
    node->count = node->left->count + node->right->count;
    return node;
}

void update(Node* node, int idx, int old_val, int new_val) {
    if (node->l == node->r) {
        if (old_val == 0) {
            node->count--;
        }
        if (new_val == 0) {
            node->count++;
        }
        return;
    }

    if (idx <= node->left->r) {
        update(node->left, idx, old_val, new_val);
    } else {
        update(node->right, idx, old_val, new_val);
    }

    node->count = node->left->count + node->right->count;
}

int query_zeros(Node* node, int l1, int r1) {
    if (node->r < l1 || node->l > r1) {
        return 0;
    }
    if (node->l >= l1 && node->r <= r1) {
        return node->count;
    }
    return query_zeros(node->left, l1, r1) + query_zeros(node->right, l1, r1);
}

int find_kth_zero(Node* node, int l1, int r1, int &k) {
    if (node->r < l1 || node->l > r1) {
        return -1;
    }

    if (node->l >= l1 && node->r <= r1) {
        if (node->count < k) {
            k -= node->count;
            return -1;
        }

        if (node->l == node->r) {
            if (k == 1) {
                return node->l;
            } else {
                k--;
                return -1;
            }
        }

        int left_k = k;
        int left_res = find_kth_zero(node->left, l1, r1, left_k);
        if (left_res != -1) {
            k = left_k;
            return left_res;
        }

        k = left_k;
        int right_res = find_kth_zero(node->right, l1, r1, k);
        return right_res;
    }

    int left_res = find_kth_zero(node->left, l1, r1, k);
    if (left_res != -1) {
        return left_res;
    }

    int right_res = find_kth_zero(node->right, l1, r1, k);
    return right_res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    Node* root = build(0, n - 1, arr);

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        char type;
        cin >> type;
        if (type == 's') {
            int l, r, kk;
            cin >> l >> r >> kk;
            l--; r--;
            int cnt = query_zeros(root, l, r);
            if (cnt < kk) {
                cout << -1 << ' ';
            } else {
                int k = kk;
                int pos = find_kth_zero(root, l, r, k);
                if (pos != -1) {
                    cout << pos + 1 << ' ';
                } else {
                    cout << -1 << ' ';
                }
            }
        } else if (type == 'u') {
            int idx, val;
            cin >> idx >> val;
            idx--;
            int old_val = arr[idx];
            arr[idx] = val;
            update(root, idx, old_val, val);
        }
    }

    return 0;
}