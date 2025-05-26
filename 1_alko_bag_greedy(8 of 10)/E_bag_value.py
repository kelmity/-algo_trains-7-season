n, m = map(int, input().split())

w = list(map(int, input().split()))

c = list(map(int, input().split()))

for i in range(n):
    w[i] = [w[i], c[i]]

c.clear()
w.sort()

for i in range(0, len(w)):
    if w[i][0] > m:
            w = w[0:i]
            break

table = [0] * (m + 1)

table[0] = 1
mx = 0

for i in range(0, len(w)):
    el = w[i]

    for k in range(m, 0, -1):
        cur_weight = k + el[0]
        cur_price = table[k] + el[1]
        if table[k] != 0 and cur_weight <= m:
            table[cur_weight] = max(table[cur_weight], cur_price)
            mx = max(mx, cur_price)

    table[el[0]] = max(table[el[0]], el[1])
    mx = max(mx, table[el[0]])

print(mx)