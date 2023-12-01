with open("1.txt") as f:
    lines = f.readlines()
    total = 0
    for string in lines:
        num_list = []
        for x in string:
            if x.isnumeric():
                num_list.append(x)
        if len(num_list) > 1:
            total += int(num_list[0] + num_list[-1])
            print(num_list[0] + num_list[-1])
        else:
            total += int(num_list[0] + num_list[0])
            print(num_list[0] + num_list[0])
print(total)
