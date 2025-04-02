n = int(input())
for i in range(0, n) :
    d, n, s, p = map(int , input().split())
    if d + n * p == n * s : print("does not matter")
    elif d + n * p > n * s : print("do not parallelize")
    else : print("parallelize")