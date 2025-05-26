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
        node -> value = arr[l];
        node -> count = 1;
        
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
        node -> count = node -> left -> count + node -> right -> count;
    }

    return node;
}

pair<int, int> find_max(Node* node, int l, int r) {
    if (node -> r < l || node -> l > r) {
        return {INF, 0};
    }
    if (node -> l >= l && node -> r <= r) {
        return {node -> value, node -> count};
    }
    
    pair<int, int> left_subtree = find_max(node -> left, l, r);
    pair<int, int> right_subtree = find_max(node -> right, l, r);

    if (left_subtree.first == right_subtree.first) {
        return {left_subtree.first, left_subtree.second + right_subtree.second};
    } else if(left_subtree.first > right_subtree.first) {
        return left_subtree;
    } else {
        return right_subtree;
    }
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
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        auto res = find_max(root, l, r);
        
        cout << res.first << " " << res.second << endl;
    }

    return 0;
}