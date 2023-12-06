def a(deets, sd, mapp):
    return min([chunk(mapp, 'seed', 'location', seed) for seed in sd])

def b(deets, sd, mapp):
    results = [expand(mapp, 'seed', 'location', seed_range) for seed_range in zip(sd[0::2], sd[1::2])]
    return min(x[0] for x in [item for sublist in results for item in sublist])

def expand(mapp, source, dest, seed_range) -> list:
    if source == dest:
        return [seed_range]
    mapping = mapp[source]
    expanded = []
    for dest_start, source_start, length in mapping[1]:
        if seed_range[0] < source_start and seed_range[0] + seed_range[1] > source_start and seed_range[0] + seed_range[1] <= source_start + length:
            left_range = (seed_range[0], source_start - seed_range[0])
            right_range = (dest_start, seed_range[1] - left_range[1])
            expanded = expanded + expand(mapp, mapping[0], dest, right_range) + expand(mapp, source, dest, left_range)
            break
        elif seed_range[0] >= source_start and seed_range[0] < source_start + length and seed_range[0] + seed_range[1] > source_start + length:
            left_range = (dest_start + seed_range[0] - source_start, source_start + length - seed_range[0])
            right_range = (source_start + length, seed_range[0] + seed_range[1] - source_start - length)
            expanded = expanded + expand(mapp, mapping[0], dest, left_range) + expand(mapp, source, dest, right_range)
            break
        elif seed_range[0] >= source_start and seed_range[0] + seed_range[1] <= source_start + length:
            expanded = expanded + expand(mapp, mapping[0], dest, (dest_start + seed_range[0] - source_start, seed_range[1]))
            break
        elif seed_range[0] < source_start and seed_range[0] + seed_range[1] > source_start + length:
            left_range = (seed_range[0], source_start - seed_range[0])
            right_range = (source_start + length, seed_range[0] + seed_range[1] - source_start - length)
            middle_range = (dest_start, length)
            expanded = expanded + expand(mapp, source, dest, right_range) + expand(mapp, mapping[0], dest, middle_range) + expand(mapp, source, dest, left_range)
            break
    if not expanded:
        expanded = expanded + expand(mapp, mapping[0], dest, seed_range)
    return expanded

def chunk(mapp, source, dest, value):
    if source == dest:
        return value
    mapping = mapp[source]
    for dest_start, source_start, length in mapping[1]:
        if source_start <= value < source_start + length:
            return chunk(mapp, mapping[0], dest, dest_start + (value - source_start))
    return chunk(mapp, mapping[0], dest, value)

def makeMap(deets):
    map_deets = deets.splitlines()
    sourceMap, destMap = map_deets[0].split()[0].split('-')[0], map_deets[0].split()[0].split('-')[2]
    translation = [list(map(int, x.split())) for x in map_deets[1:]]
    return (sourceMap, destMap, translation)

def readMap():
    with open('input') as fhand:
        return fhand.read().split('\n\n')

deets = readMap()
sd = [int(x) for x in deets[0].split()[1:]]
mapp = {makeMap(mapper)[0]: makeMap(mapper)[1:] for mapper in deets[1:]}
print(a(deets, sd, mapp))
print(b(deets, sd, mapp))
