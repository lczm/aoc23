digit = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
new_digit = ["o1e", "t2o", "thr3e", "fo4r", "f5ve", "s6x", "se7en", "ei8ht", "n9ne"]
with open("2.txt") as f:
    lines = f.readlines()
    total = 0
    for string in lines:
        for index, x in enumerate(digit):
            string = string.replace(digit[index], new_digit[index])
        num_list = []
        for x in string:
            if x.isnumeric():
                num_list.append(x)
        if len(num_list) > 1:
            total += int(num_list[0] + num_list[-1])
        else:
            total += int(num_list[0] + num_list[0])
print(total)
