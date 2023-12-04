with open("input.txt") as f:
    lines = f.read().splitlines()
    max_length = len(lines[0])
    max_height = len(lines)
    ans = 0

    all_num = []
    all_gear = []

    for index, line in enumerate(lines):
        start_count = False
        start = 0
        end = 0
        num_list = []
        gear_list = []
        for indez, x in enumerate(line):
            if x == "*":
                gear_list.append(indez)
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
        all_num.append(num_list)
        all_gear.append(gear_list)

    for row, gear_row in enumerate(all_gear):
        for gear in gear_row:
            count = 0
            mul = 1

            # Count upper limit
            for num in all_num[row-1]:
                print(num)
                if num[0] == 0:
                    start = 0
                else:
                    start = num[0] - 1
                if num[1] == max_length - 1:
                    end = max_length
                else:
                    end = num[1] + 2
                
                if gear in range(start, end):
                    mul *= int(lines[row-1][num[0]:num[1]+1])
                    count += 1

            # check for left and right
            for num in all_num[row]:
                if num[0] == 0:
                    start = 0
                else:
                    start = num[0] - 1
                if num[1] == max_length - 1:
                    end = max_length
                else:
                    end = num[1] + 2
                
                if gear in range(start, end):
                    mul *= int(lines[row][num[0]:num[1]+1])
                    count += 1

            # Count lower limit
            for num in all_num[row+1]:
                if num[0] == 0:
                    start = 0
                else:
                    start = num[0] - 1
                if num[1] == max_length - 1:
                    end = max_length
                else:
                    end = num[1] + 2
                
                if gear in range(start, end):
                    mul *= int(lines[row+1][num[0]:num[1]+1])
                    count += 1
            
            if count == 2:
                ans += mul
print("Ans: ", ans)