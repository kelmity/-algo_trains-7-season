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


int find_max(Node* node, int l, int r, int x) {
    
    if (node->r < l || node->l > r) {
        return -1;
    }
    if (node->value < x) {
        return -1;
    }
    if (node->l == node->r) {
         return node->l + 1;
    }
    int left_res = find_max(node->left, l, r, x);
    
    if (left_res != -1) {
        return left_res;
    }
    
    return find_max(node->right, l, r, x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int k;
    cin >> n >> k;
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    Node* root = build(0, n - 1, arr);
    int ln = 4;
    for (int i = 0; i < k; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, x;
            cin >> l >> x;
            l--;
            int res = find_max(root, l, n-1, x);
            cout << res << endl;

        } else if (type == 0) {
            int idx, val;
            cin >> idx >> val;
            idx--;
            update(root, idx, val);
        }
    }

    return 0;
}