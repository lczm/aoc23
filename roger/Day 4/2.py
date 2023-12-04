with open("input.txt") as f:
    lines = f.read().splitlines()

    ans = 0
    cards = []

    for index in lines:
        cards.append(1)

    for index, game in enumerate(lines):
        game_string = game[game.index(":")+2 :]
        game_list = game_string.split(" | ")
        winning_list = []
        my_list = []
        count = 0
        for indez in range(0, len(game_list[0]), 3):
            winning_list.append(int(game_list[0][indez:indez+2]))
        for indez in range(0, len(game_list[1]), 3):
            my_list.append(int(game_list[1][indez:indez+2]))

        for win in winning_list:
            if win in my_list:
                count += 1

        start = index + 1
        end = index + count + 1
        if end > len(lines):
            end = len(lines) - 1
        for x in range(start, end):
            cards[x] += cards[index]

for card in cards:
    ans += card

print(ans)