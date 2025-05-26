n, m = map(int, input().split())

w = list(map(int, input().split()))

c = list(map(int, input().split()))

for i in range(n):
    w[i] = [w[i], c[i]]

table = [[[-1, 0] for _ in range(m + 1)] for _ in range(n)]


if min(w)[0] <= m:
    st = 0
    while w[st][0] > m:
        st += 1

    #print(st)
    table[st][w[st][0]] = [st + 1, w[st][1]]
    mx = 0
    #print(w)
    #print()
    for i in range(st + 1, len(w)):
        table[i] = table[i - 1].copy()
        el = w[i]

        if el[0] <= m:
            for k in range(m, 0, -1):
                cur_weight = k + el[0]
                cur_price = table[i][k][1] + el[1]
                if table[i][k][1] != 0 and cur_weight <= m and cur_price > table[i][cur_weight][1]:
                    table[i][cur_weight] = [i + 1, cur_price]

            if table[i][el[0]][1] < el[1]:
                table[i][el[0]] = [i + 1, el[1]]



    mx = 0
    ind = 0
    '''
    for el in table:
        el.sort(key=lambda x: x[1],reverse = True)
    '''
    for i in range(1, m + 1):
        if table[n - 1][i][1] > mx:
            mx = table[n - 1][i][1]
            ind = i

    '''print(ind, table[n - 1][ind])
    print()
    '''
    #for el in table:
    #    print(el)

    array = []
    k = n - 1
    res = table[k][ind]
    cur_sm = res[1] - w[res[0] - 1][1]


    while ind != 0:

        array.append(res[0])
        ind -= w[res[0] - 1][0]
        k = res[0] - 2
        res = table[k][ind]
        #print(ind)

    array = array[::-1]

    for el in array:
        print(el)

else:
    print()


'''
4 6
200 4 1 2
1 2 5 1
'''