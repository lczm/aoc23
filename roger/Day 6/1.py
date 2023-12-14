with open("input.txt") as f:
    lines = f.read().splitlines()
    
    ans = 1
    
    time_list = lines[0].split()[1:]
    distance_list = lines[1].split()[1:]
    
    for index, time in enumerate(time_list):
        count = 0
        timer = int(time)
        record = int(distance_list[index])
        for num in range(timer+1):
            temp = num * (timer-num)
            if temp > record:
                count += 1
        ans *= count
        
print(ans)
