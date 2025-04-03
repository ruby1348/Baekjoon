for _ in range(int(input())) :
    result = ""
    arr = list(map(str, input().split()))
    for a in arr :
        count = 0
        for j in a :
            count += ord(j) - ord('a')
        count %= 27
        if count == 26 : result += " "
        else : result = result + chr(count + ord('a'))
    print(result)