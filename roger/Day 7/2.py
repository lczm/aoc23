with open("input.txt") as f:
    lines = f.read().splitlines()
    
    card_list = []
    card_rank_list = []
    bid_list = []
    
    rank = 1
    ans = 0
    for index, line in enumerate(lines):
        card_count = dict()
        count_list = []
        
        card = line.split()[0]
        bid = line.split()[1]
        card = card.replace("A", "E")
        card = card.replace("K", "D")
        card = card.replace("Q", "C")
        card = card.replace("J", "1")
        card = card.replace("T", "A")
        print(card)
        card_list.append(card)
        bid_list.append(bid)
        
        for letter in card:
            if letter not in card_count:
                card_count[letter] = 1
            else:
                card_count[letter] += 1
        
        joker = 0
        
        if "1" in card_count:
            joker = card_count["1"]
            del card_count["1"]
        for x in card_count.values():
            count_list.append(x+joker)
        count_list.sort(reverse=True)
        
        five = False
        four = False
        three = False
        two = False
        two_d = False
        added = False
        
        for num in count_list:
            if num == 5:
                card_rank_list.append(7)
                five = True
                added = True
                break
            elif num == 4:
                card_rank_list.append(6)
                four = True
                added = True
                break
            elif num == 3:
                three = True
            elif num == 2:
                if not two:
                    two = True
                    if three:
                        card_rank_list.append(5)
                        added = True
                        break
                elif two and not two_d:
                    two_d = True
                    added = True
                    card_rank_list.append(3)
                    break
        if not added:
            if three and not two:
                card_rank_list.append(4)
            elif not three and not two_d and two:
                card_rank_list.append(2)
            else:
                card_rank_list.append(1)
                
    print("Card Rank List: ", card_rank_list)
    print("Card List: ", card_list)
    print("Bid List: ", bid_list)
    for rank_no in range(1,8):
        tmp_card_list = []
        for index, rank_val in enumerate(card_rank_list):
            if rank_val == rank_no:
                tmp_card_list.append([card_list[index], index])
        tmp_card_list.sort()
        if tmp_card_list:
            print(tmp_card_list)
            for x in tmp_card_list:
                print(int(bid_list[x[1]]), rank)
                print( int(bid_list[x[1]]) * rank )
                ans += ( int(bid_list[x[1]]) * rank )
                rank += 1

print(ans)
                
        