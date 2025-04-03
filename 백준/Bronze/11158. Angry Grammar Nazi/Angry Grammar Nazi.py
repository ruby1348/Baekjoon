for _ in range(int(input())) :
    arr = list(map(str, input().split()))
    count = 0
    #u #ur
    for a in arr :
        if a == "u" or a == "ur" : count += 10
        start = 0
        #lol
        if a.find("lol", start, len(a)) != -1 : count += 10
            
    #would of, should of        
    for i in range(0, len(arr)) :
        if arr[i] == "would" or arr[i] == "should" :
            if i + 1 < len(arr) and arr[i + 1] == "of" :
                count += 10
    print(count)