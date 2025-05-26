n, m = map(int, input().split())

w = list(map(int, input().split()))

w.sort()

for i in range(0, len(w)):
    if w[i] > m:
            w = w[0:i]
            break

table = [0] * (m + 1)

table[0] = 1
mx = 0

for i in range(0, len(w)):
    el = w[i]

    for k in range(m, -1, -1):
        cur_weight = k + el

        if table[k] != 0 and cur_weight <= m:
            table[cur_weight] = 1

            mx = max(mx, cur_weight)

print(mx)