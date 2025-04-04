line = input()
result = 0
if line[0] == '0' :
    if len(line) > 1 and line[1] == 'x' :
        ##16진수
        result = int(line, 16)
    else :
        ##8진수
        result = int(line, 8)
else :
    result = int(line)
print(result)