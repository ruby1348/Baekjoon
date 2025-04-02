for _ in range(int(input())) :
    result = False
    a, b, c, s, t = map(int, input().split())
    if b * b >= 4 * a * c :
        x1 = (-b - (b * b - 4 * a * c)**(1/2)) / (2 * a)
        x2 = (-b + (b * b - 4 * a * c)**(1/2)) / (2 * a)
        if x1 >= s and x1 <= t : result = True
        if x2 >= s and x2 <= t : result = True
    if result : print("Yes")
    else : print("No")