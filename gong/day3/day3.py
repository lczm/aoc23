# Dear God above, please let this code run, amen.

def parse() -> {(int):str}:
    fin:{(int):str} = {}
    with open("input","r") as fhand:
        data_array:[[str]] = [line.rstrip() for line in fhand]
    for y in range(len(data_array)):
        for x in range(len(data_array[y])):
            fin[(x,y)] = data_array[y][x]
    return fin

def check_range(parsed:{(int):str},coord:(int)) -> bool:
    return coord in parsed

def full_number(parsed:{(int):str},coord:(int)) -> int:

    # pos1 pos2 pos3 pos4 pos5

    fin:str = ""
    pos1 = (coord[0]-2, coord[1])
    pos2 = (coord[0]-1, coord[1])
    pos3 = coord
    pos4 = (coord[0]+1, coord[1])
    pos5 = (coord[0]+2, coord[1])

    if check_range(parsed,pos1) and parsed[pos1].isnumeric():
        if check_range(parsed,pos2) and parsed[pos2].isnumeric():
            fin = f"{parsed[pos1]}{parsed[pos2]}{parsed[pos3]}"
            return int(fin)
        else:
            pass

    if check_range(parsed,pos2) and parsed[pos2].isnumeric():
        if check_range(parsed,pos4) and parsed[pos4].isnumeric():
            fin = f"{parsed[pos2]}{parsed[pos3]}{parsed[pos4]}"
            return int(fin)
        else:
            fin = f"{parsed[pos2]}{parsed[pos3]}"
            return int(fin)

    if check_range(parsed,pos4) and parsed[pos4].isnumeric():
        if check_range(parsed,pos5) and parsed[pos5].isnumeric():
            fin = f"{parsed[pos3]}{parsed[pos4]}{parsed[pos5]}"
            return int(fin)
        else:
            fin = f"{parsed[pos3]}{parsed[pos4]}"
            return int(fin)

    return int(parsed[pos3])

def check_adjacent(parsed:{(int):str},curr_coord:(int)) -> bool:

    # sq1 sq2 sq3
    # sq4 sq5 sq6
    # sq7 sq8 sq9

    valid:str= "1234567890."

    sq1 = (curr_coord[0]-1,curr_coord[1]-1)
    sq2 = (curr_coord[0],curr_coord[1]-1)
    sq3 = (curr_coord[0]+1,curr_coord[1]-1)
    sq4 = (curr_coord[0]-1, curr_coord[1])
    sq5 = curr_coord
    sq6 = (curr_coord[0]+1, curr_coord[1])
    sq7 = (curr_coord[0]-1, curr_coord[1]+1)
    sq8 = (curr_coord[0], curr_coord[1]+1)
    sq9 = (curr_coord[0]+1, curr_coord[1]+1)

    if check_range(parsed,sq1) and parsed[sq1] not in valid:
        return True

    if check_range(parsed,sq2) and parsed[sq2] not in valid:
        return True

    if check_range(parsed,sq3) and parsed[sq3] not in valid:
        return True

    if check_range(parsed,sq4) and parsed[sq4] not in valid:
        return True

    if check_range(parsed,sq6) and parsed[sq6] not in valid:
        return True

    if check_range(parsed,sq7) and parsed[sq7] not in valid:
        return True

    if check_range(parsed,sq8) and parsed[sq8] not in valid:
        return True

    if check_range(parsed,sq9) and parsed[sq9] not in valid:
        return True

    return False

def a() -> int:
    matrix:{(int):str}= parse()
    num_buffer:[int]= []
    for coord in matrix:
        if matrix[coord].isnumeric() and check_adjacent(matrix,coord):
            curr = full_number(matrix, coord)
            if not num_buffer or num_buffer[-1] != curr:
                num_buffer.append(full_number(matrix,coord))
    return sum(num_buffer)

def count_adjacent(parsed:{(int):str},curr_coord:(int)) -> (int,[int]):

    # sq1 sq2 sq3
    # sq4  *  sq6
    # sq7 sq8 sq9

    valid:str = "1234567890"

    adjacent_count:int = 0
    adjacent_nums:[int] = []
    
    sq1 = (curr_coord[0]-1,curr_coord[1]-1)
    sq2 = (curr_coord[0],curr_coord[1]-1)
    sq3 = (curr_coord[0]+1,curr_coord[1]-1)
    sq4 = (curr_coord[0]-1, curr_coord[1])
    sq6 = (curr_coord[0]+1, curr_coord[1])
    sq7 = (curr_coord[0]-1, curr_coord[1]+1)
    sq8 = (curr_coord[0], curr_coord[1]+1)
    sq9 = (curr_coord[0]+1, curr_coord[1]+1)

    if check_range(parsed, sq1) and parsed[sq1] in valid:
        if not adjacent_nums or adjacent_nums[-1] != full_number(parsed,sq1):
            adjacent_nums.append(full_number(parsed,sq1))
            adjacent_count += 1

    if check_range(parsed, sq2) and parsed[sq2] in valid:
        if not adjacent_nums or adjacent_nums[-1] != full_number(parsed,sq2):
            adjacent_nums.append(full_number(parsed,sq2))
            adjacent_count += 1

    if check_range(parsed, sq3) and parsed[sq3] in valid:
        if not adjacent_nums or adjacent_nums[-1] != full_number(parsed,sq3):
            adjacent_nums.append(full_number(parsed,sq3))
            adjacent_count += 1

    if check_range(parsed, sq4) and parsed[sq4] in valid:
        if not adjacent_nums or adjacent_nums[-1] != full_number(parsed,sq4):
            adjacent_nums.append(full_number(parsed,sq4))
            adjacent_count += 1

    if check_range(parsed, sq6) and parsed[sq6] in valid:
        if not adjacent_nums or adjacent_nums[-1] != full_number(parsed,sq6):
            adjacent_nums.append(full_number(parsed,sq6))
            adjacent_count += 1

    if check_range(parsed, sq7) and parsed[sq7] in valid:
        if not adjacent_nums or adjacent_nums[-1] != full_number(parsed,sq7):
            adjacent_nums.append(full_number(parsed,sq7))
            adjacent_count += 1

    if check_range(parsed, sq8) and parsed[sq8] in valid:
        if not adjacent_nums or adjacent_nums[-1] != full_number(parsed,sq8):
            adjacent_nums.append(full_number(parsed,sq8))
            adjacent_count += 1

    if check_range(parsed, sq9) and parsed[sq9] in valid:
        if not adjacent_nums or adjacent_nums[-1] != full_number(parsed,sq9):
            adjacent_nums.append(full_number(parsed,sq9))
            adjacent_count += 1

    return (adjacent_count,adjacent_nums)

def b() -> int:
    matrix:{(int):str}= parse()
    num_buffer:[int] = []
    for coord in matrix:
        if matrix[coord] == "*" and count_adjacent(matrix,coord)[0] == 2:
            num_buffer.append(count_adjacent(matrix,coord)[1][0] * count_adjacent(matrix,coord)[1][1])
    return sum(num_buffer)

print(a())
print(b())
