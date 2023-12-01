
digit = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
with open("2.txt") as f:
    lines = f.readlines()
    total = 0
    for string in lines:
        tmp_str = ""
        num_list = []
        for x in string:
            if x.isnumeric():
                num_list.append(x)
                tmp_str = ""
            else:
                tmp_str += x
                for index, name in enumerate(digit):
                    if name in tmp_str:
                        num_list.append(str(index+1))
                        tmp_str = tmp_str[-2:]

        if len(num_list) > 1:
            total += int(num_list[0] + num_list[-1])
        else:
            total += int(num_list[0] + num_list[0])
print(total)
