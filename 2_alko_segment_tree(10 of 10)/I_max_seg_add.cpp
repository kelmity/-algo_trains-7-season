#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Node {
    int l, r;
    long long add;
    long long value;
    Node* left;
    Node* right;

    Node(int l, int r) : l(l), r(r), add(0), value(0), left(nullptr), right(nullptr) {}
};

Node* build(int l, int r, const vector<long long>& arr) {
    Node* node = new Node(l, r);
    
    if (l == r) {
        node -> value = arr[l];
        return node;
    }
    
    int mid = (l + r) / 2;
    node -> left = build(l, mid, arr);
    node -> right = build(mid + 1, r, arr);

    node -> value = max(node -> left -> value, node -> right -> value);

    return node;
}


void update(Node* node, int l1, int r1, long long add) {
    if (node->r < l1 || node->l > r1) {
        return;
    }
    if (l1 <= node->l && node->r <= r1) {
        node->add += add;
        node->value += add;
        return;
    }
    if (node->left) {
        node->left->add += node->add;
        node->left->value += node->add;
        node->right->add += node->add;
        node->right->value += node->add;
        node->add = 0;
    }

    update(node->left, l1, r1, add);
    update(node->right, l1, r1, add);
    node->value = max(node->left->value, node->right->value);
}

long long get_value(Node* node, int l, int r, long long sm = 0) {
    if (node->r < l || node->l > r) {
        return -1;
    }
    if (l <= node->l && node->r <= r) {
        return node->value;
    }
    if (node->left) {
        node->left->add += node->add;
        node->left->value += node->add;
        node->right->add += node->add;
        node->right->value += node->add;
        node->add = 0;
    }

    return max(get_value(node->left, l, r), get_value(node->right, l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    Node* root = build(0, n - 1, arr);

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        char type;
        cin >> type;
        if (type == 'a') {
            int l, r;
            long long add;
            cin >> l >> r >> add;
            l--; r--;
            update(root, l, r, add);
        } else if (type == 'm') {
            int l, r;
            cin >> l >> r;
            l--; r--;
            cout << get_value(root, l, r) << ' ';
        }
    }

    return 0;
}