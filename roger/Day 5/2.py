with open("test.txt") as f:
    lines = f.read().splitlines()

    seeds_list = lines[0][lines[0].index(":")+2:].split(" ")
    actual_seed_list = []
    for index, seed in enumerate(seeds_list):
        if index % 2 == 0:
            start = int(seed)
        else:
            end = start + int(seed) - 1
            actual_seed_list.append([start, end])
    
    print(actual_seed_list)

    tmp_seeds_list = []

    for line in lines[2:]:
        if not line:
            actual_seed_list = tmp_seeds_list.copy()
            print("UPDATED: ", actual_seed_list)
            continue
        if line[0].isalpha():
            tmp_seeds_list = []
        if line[0].isdigit():
            num_list = line.split(" ")
            source_start = int(num_list[1])
            source_end = int(num_list[1]) + int(num_list[2]) - 1

            destination_start = int(num_list[0])
            destination_end = int(num_list[0]) + int(num_list[2]) - 1

            print(source_start, source_end, destination_start, destination_end)

            for index, seed in enumerate(actual_seed_list):
                start = seed[0]
                end = seed[1]
                if start in range(source_start, source_end+1):
                    start = (seed[0] - source_start) + destination_start
                    if end in range(source_start, source_end+1):
                        end = (seed[1] - source_start) + destination_start
                    else:
                        end = destination_end
                        tmp_seeds_list.append([source_end+1, seed[1]])
                    tmp_seeds_list.append([start, end])
                elif end in range(source_start, source_end+1):
                    end = (seed[1] - source_start) + destination_start
                    tmp_seeds_list.append([destination_start, end])
                    tmp_seeds_list.append([seed[0], source_start-1])
        print(tmp_seeds_list)
                
        
    actual_seed_list = tmp_seeds_list.copy()
    print(actual_seed_list)