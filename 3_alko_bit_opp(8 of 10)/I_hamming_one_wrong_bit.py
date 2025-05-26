'''
111111
111000
111110
'''


n = int(input())
x = input()
if n == 1:
    m = len(x)
    r = 0
    while (1 << r) < m + r + 1:
        r += 1
    total_len = m + r
    #print(r)
    table = []
    ind = 0
    for i in range(1, total_len + 1):
        if (i & (i - 1)) == 0:
            table.append(0)
        else:
            if ind < m:
                table.append(int(x[ind]))
                ind += 1
            else:
                table.append(0)

    for pow in range(r):
        cur_pow = 1 << pow
        sm = 0
        for i in range(total_len):
            if (i + 1) & cur_pow != 0:
                sm += table[i]

        table[cur_pow - 1] = ((sm + 1) % 2)

    print(''.join(map(str, table)))
else:
    ln = len(x)
    r = 0
    while (1 << r) < ln:
        r += 1

    k = 0
    while (1 << k) < ln - r:
        k += 1

    ans = 0

    for pow in range(r):
        sm = 0
        cur_pow = 1 << pow
        if cur_pow > ln:
            break
        for i in range(ln):
            if (i + 1) & cur_pow != 0:
                #print(i + 1, end = " ")
                sm += int(x[i])
        #print(sm, cur_pow)
        if sm % 2 != 1:
            ans += int(cur_pow)
        #print()

    #print(ans)
    d = list(x)
    if ans > 0:
        if d[ans - 1] == '0':
            d[ans - 1] = '1'
        else:
            d[ans - 1] = '0'

    res = []
    ind = 0
    for i in range(1, ln + 1):
        if (i & (i - 1)) != 0:
            if ind < (ln - r + 1):
                res.append(d[i - 1])
                ind += 1
    k = ''.join(res)
    print(k)
"""
1
0101110110
out - 11011011110110
2
in - 01011011110110

3
10011010

110000011111

4
1011000
"""
