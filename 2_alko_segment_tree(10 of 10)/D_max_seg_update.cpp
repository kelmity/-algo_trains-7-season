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

    Node(int l1, int r1): l(l1), r(r1), value(0), count(-1), left(nullptr), right(nullptr) {}
    
};

const int INF = INT_MIN;

void update(Node* node, int count, int new_value) {
    if (node->l == node->r) {
        node->value = new_value;
        return;
    }
    if (count <= node->left->r) {
        update(node->left, count, new_value);
    } else {
        update(node->right, count, new_value);
    }
    node->value = max(node->left->value, node->right->value);
}

Node* build(int l, int r, const vector<int>& arr) {
    Node* node = new Node(l, r);
    
    if (l == r) {
        node -> value = arr[l];
        node -> count = l;
        
        return node;
    }
    
    int mid = (l + r) / 2;
    node -> left = build(l, mid, arr);
    node -> right = build(mid + 1, r, arr);

    if (node -> left -> value > node -> right -> value) {
        node -> value = node -> left -> value;
        node -> count = node -> left -> count;
    } else if(node -> right -> value > node -> left -> value) {
        node -> value = node -> right -> value;
        node -> count = node -> right -> count;
    } else {
        node -> value = node -> left -> value;
        node -> count = node -> left -> count;
    }

    return node;
}

int find_max(Node* node, int l, int r) {
    if (node -> r < l || node -> l > r) {
        return INF;
    }
    if (node -> l >= l && node -> r <= r) {
        return node -> value;
    }
    
    int left_subtree = find_max(node -> left, l, r);
    int right_subtree = find_max(node -> right, l, r);

    return max(left_subtree, right_subtree);
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
            int l, r;
            cin >> l >> r;
            l--; r--;
            cout << find_max(root, l, r) << " ";
        } else if (type == 'u') {
            int idx, val;
            cin >> idx >> val;
            idx--;
            update(root, idx, val);
        }
    }

    return 0;
}