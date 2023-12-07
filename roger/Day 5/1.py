with open("input.txt") as f:
    lines = f.read().splitlines()

    seeds_list = lines[0][lines[0].index(":")+2:].split(" ")

    for index, seed in enumerate(seeds_list):
        seeds_list[index] = int(seed)
    # seeds_list.sort()
    print(seeds_list)
    tmp_seeds_list = seeds_list.copy()

    for line in lines:
        if not line:
            seeds_list = tmp_seeds_list.copy()
            print("UPDATED: ", seeds_list)
            continue
        if line[0].isdigit():
            num_list = line.split(" ")
            source_start = int(num_list[1])
            source_end = int(num_list[1]) + int(num_list[2]) - 1

            destination_start = int(num_list[0])
            destination_end = int(num_list[0]) + int(num_list[2]) - 1

            print(source_start, source_end, destination_start, destination_end)

            for index, seed in enumerate(seeds_list):
                if seed in range(source_start, source_end+1):
                    new_seed = (seed - source_start) + destination_start
                    tmp_seeds_list[index] = new_seed
        print(tmp_seeds_list)
                
        
    seeds_list = tmp_seeds_list.copy()
    print(min(seeds_list))