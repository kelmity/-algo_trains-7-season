#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<vector<unsigned int>> arr(n);

    for(int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            unsigned int el;
            cin >> el;
            arr[i].push_back(el);
        }
    }
    
    vector<unsigned> res(n, 0);

    for (int i = 0; i < n - 1; ++i) {
        for (int k = i + 1; k < n; ++k) {
            int val = arr[i][k];
            res[i] |= val;
            res[k] |= val;
        }
    }

    for (auto el: res) {
        cout << el << " ";
    }

    return 0;
    
}
