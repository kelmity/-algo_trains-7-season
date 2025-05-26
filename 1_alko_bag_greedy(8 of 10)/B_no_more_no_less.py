t = int(input())

for _ in range(t):
    n = int(input())
    ptr = 0
    arr = list(map(int, input().split()))
    res = []
    st = 0

    while st < n:
        cur_mn = arr[st]
        cur_ln = 1
        end = st

        while end + 1 < n:
            nx_end = end + 1
            new_mn = min(cur_mn, arr[nx_end])
            new_ln = cur_ln + 1

            if new_ln > new_mn:
                break

            cur_mn = new_mn
            cur_ln = new_ln
            end = nx_end

        res.append(cur_ln)
        st = end + 1

    print(len(res))
    for el in res:
        print(el, end = " ")
    print()