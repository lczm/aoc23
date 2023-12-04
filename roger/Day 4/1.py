with open("input.txt") as f:
    lines = f.read().splitlines()

    ans = 0

    for game in lines:
        game_string = game[game.index(":")+2 :]
        game_list = game_string.split(" | ")
        winning_list = []
        my_list = []
        points = 0
        count = False
        for index in range(0, len(game_list[0]), 3):
            winning_list.append(int(game_list[0][index:index+2]))
        for index in range(0, len(game_list[1]), 3):
            my_list.append(int(game_list[1][index:index+2]))

        for win in winning_list:
            if win in my_list:
                if not count:
                    points = 1
                    count = True
                else:
                    points *= 2
        print(points)
        
        ans += points

print(ans)