from functools import reduce
from math import gcd

def lcm(numbers):
    return reduce((lambda x, y: int(x * y / gcd(x, y))), numbers)


with open("input.txt") as f:
    lines = f.read().splitlines()
    
    instructions = [x for x in lines[0]]
    coords = []
    next_coords = []
    nodes = []
    first_encounter_coords = []
    count = 0

    for line in lines[2:]:
        tmp_next = []
        coords.append(line[:3])
        tmp_next.append(line[7:10])
        tmp_next.append(line[12:15])
        next_coords.append(tmp_next)
        
        if line[2] == "A":
            nodes.append(line[:3])
    
    #['GNA', 'FCA', 'AAA', 'MXA', 'VVA', 'XHA']

    for node in nodes:
        count = 0
        while node[2] != "Z":
            for instruction in instructions:
                index = coords.index(node)
                if instruction == "L":
                    node = next_coords[index][0]
                else:
                    node = next_coords[index][1]
                count += 1
                if node[2] == "Z":
                    first_encounter_coords.append(count)
                    break

    print(lcm(first_encounter_coords))