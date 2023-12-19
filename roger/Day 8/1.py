with open("input.txt") as f:
    lines = f.read().splitlines()
    
    instructions = [x for x in lines[0]]
    coords = []
    next_coords = []
    count = 0
    
    for line in lines[2:]:
        tmp_next = []
        coords.append(line[:3])
        tmp_next.append(line[7:10])
        tmp_next.append(line[12:15])
        next_coords.append(tmp_next)
    
    node = "AAA"
    
    while node != "ZZZ":
        for instruction in instructions:
            index = coords.index(node)
            if instruction == "L":
                node = next_coords[index][0]
            else:
                node = next_coords[index][1]
            count += 1
            
    print(count)