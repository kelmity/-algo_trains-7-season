#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> keys(n);
    for (int i = 0; i < n; ++i) {
        cin >> keys[i];
    }
    vector<bool> vis(n + 1, false);
    int res = 0;

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            int cur = i;
            vector<int> path;
            while (true) {
                if (vis[cur]) {
                    break;
                }
                auto it = find(path.begin(), path.end(), cur);
                if (it != path.end()) {
                    
                    res += 1;
                    break;
                }
                path.push_back(cur);
                cur = keys[cur - 1];
            }
            for (int node : path) {
                vis[node] = true;
            }
        }
    }

    cout << res << endl;
    return 0;
}