n = int(input())
total = [0] * (n + 1)
prev = [0] * (n + 1)

sum_total = 0

for i in range(1, n + 1):
    t, m = map(int, input().split())
    if m > 0:
        total[i] = total[t] + m
        prev[i] = t
    else:
        total[i] = total[prev[t]]
        prev[i] = prev[prev[t]]

    sum_total += total[i]

print(sum_total)