#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    unsigned long long x;
    cin >> x;

    int res = 0;

    while (x) {
        x &= x - 1;
        res++;
    }
    
    cout << res;
 
    return 0;
}