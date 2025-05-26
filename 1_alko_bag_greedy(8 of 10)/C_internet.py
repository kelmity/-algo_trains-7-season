from math import log

m = int(input())
a = list(map(int, input().split()))
k = (int(log(m, 2)))

a = a[0: k + 1]

a = [[a[i]/2**i, a[i], i] for i in range(len(a))]

a.sort(reverse = True)
for i in range(0, len(a)):
    if a[i][0] < 1:
        a = a[0:i]
        break

mn = 2 ** (k + 1)
res = 0
k = 0
j = 0
i = a[0][1]
cost = 2**a[0][2]

while m != 0 and k < mn:

    if m > i:
        dif = m // i
        m -= dif * i
        k += cost * dif
        if m == 0:
            mn = min(mn, k)

    elif m == i:
        mn = min(mn, k + cost)
        m -= i

    else:
        j += 1
        mn = min(mn, k + cost)
        
        if j == len(a):
            break

        i = a[j][1]
        cost = 2**a[j][2]

print(mn)

