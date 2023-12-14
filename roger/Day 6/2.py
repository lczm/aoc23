with open("input.txt") as f:
    lines = f.read().splitlines()
    
    ans = 0
    
    time_list = lines[0].split()[1:]
    distance_list = lines[1].split()[1:]
    
    act_time = ""
    act_distance = ""
    
    for time in time_list:
        act_time += time
    
    for distance in distance_list:
        act_distance += distance
        
    act_time = int(act_time)
    act_distance = int(act_distance)
    
    for num in range(act_time+1):
        temp = num * (act_time-num)
        if temp > act_distance:
            ans += 1
print(ans)