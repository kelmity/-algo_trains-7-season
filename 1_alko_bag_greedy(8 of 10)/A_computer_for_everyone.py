n, m = map(int, input().split())

x = list(map(int, input().split()))
y = list(map(int, input().split()))
y = [[y[i], i] for i in range(len(y))]
x = [[x[i], i] for i in range(len(x))]
x.sort()
y.sort()
arr = [0] * n
k = 0
j = 0
cnt = 0

while (k != n and j != m):

    if x[k][0] < y[j][0]:
        arr[x[k][1]] = (y[j][1] + 1)
        cnt += 1
        k += 1
        j += 1
    else:
        j += 1

print(cnt)
for el in arr:
    print(el)
