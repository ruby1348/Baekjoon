for _ in range(int(input())) :
    count = 0
    e, n = map(int, input().split())
    for i in range(n) :
        temp = int(input())
        if temp > e : count += 1
    print(count)