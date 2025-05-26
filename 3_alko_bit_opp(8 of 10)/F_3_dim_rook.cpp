#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

bool is_matrix_covered(const vector<vector<unsigned long>>& mat, int n, int num_blocks) {
    for (int a = 1; a <= n; ++a) {
        bool row_covered = true;
        for (int el = 0; el < num_blocks;
            \ ++el) {
            unsigned long mask = mat[a][el];
            if (el == num_blocks - 1) {
                int bits_needed = n % 64;
                if (bits_needed == 0) bits_needed = 64;
                unsigned long expected;
                if (bits_needed == 64) {
                    expected = ~0ULL;
                } else {
                    expected = (1ULL << bits_needed) - 1;
                }
                if ((mask & expected) != expected) {
                    row_covered = false;
                    break;
                }
            } else {
                if (mask != ~0ULL) {
                    row_covered = false;
                    break;
                }
            }
        }
        if (!row_covered) {
            return false;
        }
    }
    return true;
}

int find_z(int x, int y, int n, int num_blocks, const vector<vector<unsigned long>>& xz, const vector<vector<unsigned long>>& yz) {
    for (int el = 0; el < num_blocks; ++el) {
        unsigned long xz_mask = xz[x][el];
        unsigned long yz_mask = yz[y][el];
        unsigned long combined = xz_mask | yz_mask;
        unsigned long all_ones;
        if (el == num_blocks - 1) {
            int bits_needed = n % 64;
            if (bits_needed == 0) bits_needed = 64;
            if (bits_needed == 64) {
                all_ones = ~0ULL;
            } else {
                all_ones = (1ULL << bits_needed) - 1;
            }
        } else {
            all_ones = ~0ULL;
        }
        unsigned long available = ~combined & all_ones;
        if (available == 0) continue;
        int pos = __builtin_ctzll(available);
        int z = el * 64 + pos + 1;
        if (z > n) continue;
        return z;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<vector<bool>> xy(n + 1, vector<bool>(n + 1, false));
    int count_xy = 0;

    int num_blocks = (n + 63) / 64;

    vector<vector<unsigned long>> xz(n + 1, vector<unsigned long>(num_blocks, 0));
    vector<vector<unsigned long>> yz(n + 1, vector<unsigned long>(num_blocks, 0));

    for (int i = 0; i < k; ++i) {
        int a, b, c;
        cin >> a >> b >> c;

        if (!xy[a][b]) {
            xy[a][b] = true;
            count_xy++;
        }

        int el = (c - 1) / 64;
        int pos = (c - 1) % 64;
        xz[a][el] |= (1ULL << pos);
        yz[b][el] |= (1ULL << pos);
    }

    if (count_xy == n * n) {
        cout << "YES" << endl;
        return 0;
    }

    if (is_matrix_covered(xz, n, num_blocks)) {
        cout << "YES" << endl;
        return 0;
    }

    if (is_matrix_covered(yz, n, num_blocks)) {
        cout << "YES" << endl;
        return 0;
    }

    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= n; ++y) {
            if (!xy[x][y]) {
                int z = find_z(x, y, n, num_blocks, xz, yz);
                if (z != -1) {
                    cout << "NO" << endl;
                    cout << x << " " << y << " " << z << endl;
                    return 0;
                }
            }
        }
    }

    cout << "YES" << endl;

    return 0;
}