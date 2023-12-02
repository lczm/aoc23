with open("input.txt") as f:
    lines = f.read().splitlines()
    sum = 0
    for id in lines:
        default_colour = {"red": 0, "green": 0, "blue": 0}
        multiplication = 1
    
        game_string = id[id.index(":")+2 :]
        game_list = game_string.split("; ")
        for game in game_list:
            colour_list = game.split(", ")
            for colour in colour_list:
                colour = colour.split(" ")
                if int(colour[0]) > default_colour[colour[1]]:
                    default_colour[colour[1]] = int(colour[0])
        for x in default_colour:
            multiplication *= default_colour[x]
        sum += multiplication
print(sum)