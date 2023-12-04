with open("input.txt") as f:
    lines = f.read().splitlines()
    max_length = len(lines[0])
    max_height = len(lines)
    ans = 0

    for index, line in enumerate(lines):
        start_count = False
        start = 0
        end = 0
        num_list = []
        for indez, x in enumerate(line):
            if x.isdigit():
                if not start_count:
                    start_count = True
                    start = indez
            else:
                if start_count:
                    start_count = False
                    end = indez-1
                    num_list.append((start, end))
        if x.isdigit() and start_count:
            start_count = False
            end = indez
            num_list.append((start, end))
        
        for place in num_list:
            add = False
            # check upper limits
            if index != 0:
                if place[0] == 0:
                    start = 0
                else:
                    start = place[0] - 1
                if place[1] == max_length - 1:
                    end = max_length
                else:
                    end = place[1] + 2

                for x in (lines[index-1][start:end]):
                    if not x.isalnum() and x != ".":
                        add = True
            
            # check for left and right
            if place[0] != 0:
                if not (lines[index][place[0]-1]).isalnum() and (lines[index][place[0]-1]) != ".":
                    add = True
            if place[1] != max_length - 1:
                if not (lines[index][place[1]+1]).isalnum() and (lines[index][place[1]+1]) != ".":
                    add = True

            # check for lower limits
            if index != max_height-1:
                if place[0] == 0:
                    start = 0
                else:
                    start = place[0] - 1
                if place[1] == max_length - 1:
                    end = max_length
                else:
                    end = place[1] + 2

                for x in (lines[index+1][start:end]):
                    if not x.isalnum() and x != ".":
                        add = True

            if add:
                ans += int(line[place[0]:place[1]+1])

print("Ans: ", ans)