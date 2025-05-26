#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    
    for (int i = 0; i < n; i++) { 
        cin >> a[i];
    }

    if (n <= 2) {
        cout << "0 0";
        return 0;
    }

    vector<int> prev(n), next(n);
    
    for (int i = 0; i < n; i++) {
        prev[i] = (i - 1 + n) % n;
        next[i] = (i + 1) % n;
    }

    vector<int> res(n);
    vector<bool> dead(n);
    vector<int> cands;

    for (int i = 0; i < n; i++) {
        int l = prev[i], r = next[i];
        if (a[i] < a[l] && a[i] < a[r]) cands.push_back(i);
    }

    int round = 1, left = n;
    vector<bool> in_cand(n);

    while (!cands.empty()) {
        vector<int> remove, new_cand;
        in_cand.assign(n, false);

        for (int x : cands) {
            if (dead[x]) continue;
            int l = prev[x], r = next[x];
            if (a[x] >= a[l] || a[x] >= a[r]) continue;
            remove.push_back(x);
        }

        if (remove.empty()) break;

        int new_left = left - remove.size();
        if (new_left <= 2) {
            for (int x : remove) res[x] = round;
            break;
        }
        left = new_left;

        for (int x : remove) {
            dead[x] = true;
            res[x] = round;
            int l = prev[x], r = next[x];
            prev[r] = l;
            next[l] = r;

            if (!dead[l] && !in_cand[l]) {
                new_cand.push_back(l);
                in_cand[l] = true;
            }
            if (!dead[r] && !in_cand[r]) {
                new_cand.push_back(r);
                in_cand[r] = true;
            }
        }

        cands = move(new_cand);
        round++;
    }

    for (auto el : res) {
        cout << el << " ";
    }
    return 0;
}