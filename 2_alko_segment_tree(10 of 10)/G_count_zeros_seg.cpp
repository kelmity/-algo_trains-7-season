#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    int mx;
    int pref;
    int suf;
    int size;

    Segment() : mx(0), pref(0), suf(0), size(0) {}
    Segment(int val) {
        size = 1;
        if (val == 0) {
            mx = 1;
            pref = 1;
            suf = 1;
        } else {
            mx = 0;
            pref = 0;
            suf = 0;
        }
    }
};

Segment combine(const Segment& a, const Segment& b) {
    Segment res;
    res.size = a.size + b.size;
    res.pref = (a.pref == a.size) ? (a.size + b.pref) : a.pref;
    res.suf = (b.suf == b.size) ? (b.size + a.suf) : b.suf;
    res.mx = max({a.mx, b.mx, a.suf + b.pref});
    return res;
}

struct Node {
    int l, r;
    Segment seg;
    Node* left;
    Node* right;

    Node(int l1, int r1) : l(l1), r(r1), left(nullptr), right(nullptr) {}
};

Node* build(int l, int r, const vector<int>& arr) {
    Node* node = new Node(l, r);

    if (l == r) {
        node->seg = Segment(arr[l]);
        return node;
    }

    int mid = (l + r) / 2;
    node->left = build(l, mid, arr);
    node->right = build(mid + 1, r, arr);
    node->seg = combine(node->left->seg, node->right->seg);
    return node;
}

void update(Node* node, int idx, int new_val) {
    if (node->l == node->r) {
        node->seg = Segment(new_val);
        return;
    }

    if (idx <= node->left->r) {
        update(node->left, idx, new_val);
    } else {
        update(node->right, idx, new_val);
    }

    node->seg = combine(node->left->seg, node->right->seg);
}

Segment query(Node* node, int l, int r) {
    if (node->r < l || node->l > r) {
        return Segment();
    }
    if (l <= node->l && node->r <= r) {
        return node->seg;
    }

    Segment left_seg = query(node->left, l, r);
    Segment right_seg = query(node->right, l, r);

    if (left_seg.size == 0) {
        return right_seg;
    }
    if (right_seg.size == 0) {
        return left_seg;
    }

    return combine(left_seg, right_seg);
}

void print(Node* node, int d) {
    if (!node) {
        return;
    }

    cout << "[" << node->l << ", " << node->r << "] "
         << "max: " << node->seg.mx
         << " | pref: " << node->seg.pref
         << " | suff: " << node->seg.suf
         << " | size: " << node->seg.size << endl;
    
    print(node->left, d + 1);
    print(node->right, d + 1);
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

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string type;
        cin >> type;
        if (type == "QUERY") {
            int l, r;
            cin >> l >> r;
            l--; r--;
            Segment seg = query(root, l, r);
            cout << seg.mx << endl;
        } else if (type == "UPDATE") {
            int idx, val;
            cin >> idx >> val;
            idx--;
            update(root, idx, val);
            //print(root, 0);
        }
    }

    return 0;
}