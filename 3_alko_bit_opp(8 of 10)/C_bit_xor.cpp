#include <iostream>
#include <vector>

using namespace std;

int cnt_ones(unsigned int x) {
    int res = 0;

    while (x) {
        x &= x - 1;
        res++;
    }
    return res;

}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<unsigned long long> arr(n);
    int total = 0;
    int mx_ones = 0;

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        int c = cnt_ones(arr[i]);
        total += c;
        mx_ones = max(c, mx_ones);
    }

    if (total - (2 * mx_ones) < 0 || total % 2 != 0) {
        cout << "impossible";
        
        return 0;
    }



}