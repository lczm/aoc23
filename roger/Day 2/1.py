default_colour = {"red": 12, "green": 13, "blue": 14}

with open("input.txt") as f:
    lines = f.read().splitlines()
    possible = 0
    for id in lines:
        exceed = False
        tmp_possible = 0
        id_number = int(id[id.index("Game ") + 5: id.index(":")]) 
        game_string = id[id.index(":")+2 :]
        game_list = game_string.split("; ")
        for game in game_list:
            colour_list = game.split(", ")
            for colour in colour_list:
                colour = colour.split(" ")
                if int(colour[0]) > default_colour[colour[1]]:
                    exceed = True
        if not exceed:
            possible += id_number
print(possible)
        