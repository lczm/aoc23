def small(arr:[str]) -> int:
    return min([int(val) for val in arr])

def big(arr:[str]) -> int:
    try:
        return max([int(val) for val in arr])
    except:
        arr = arr[0] # make this line optional
        return max([int(val) for val in arr])

def chunk(arr:[str]) -> [[str]]:
    fin:[[str]] = []
    tem:[str] = []
    for i in range(len(arr)):
        tem.append(arr[i])
        if (i + 1) % 3 == 0 or i == len(arr) - 1:
            fin.append(tem)
            tem = []
    return fin

def parse() -> {str:str}:
    fin:{str:str} = {}
    with open("input","r") as fhand: 
        buf:str = ""
        inter:[str] = []
        for line in [line.rstrip() for line in fhand]:
            # print(line)
            if line == "":
                inter.append(buf)
                buf = ""
            buf += f"{line} "
        inter.append(buf)
        for el in inter:
            if el.split(":")[0].strip() == "seeds":
                fin[el.split(":")[0].strip()] = [el.split(":")[1].strip().split(" ")]
            else:
                fin[el.split(":")[0].strip()] = chunk(el.split(":")[1].strip().split(" "))
    return fin

def gen_map(loc:[[str]],ls:str) -> {str:str}:
    # print(f"FFFFFFF{loc}")
    fin:{str:str} = {}
    for el in loc:
        # print(f"ELLLYEAHHHH {el}")
        dest_range_start:int = int(el[0])
        src_range_start:int = int(el[1])
        range_len:int = int(el[2])
        for q in range(src_range_start, src_range_start + range_len):
            fin[str(q)] = str(dest_range_start)
            dest_range_start += 1
    for i in range(int(ls)+1):
        if str(i) not in fin:
            fin[str(i)] = str(i)
    return fin

def map_val(mapp:{str:str},src:[str]) -> [str]:
    fin:[str] = []
    try:
        for el in src:
            fin.append(mapp[el])
    except:
        for el in src[0]:
            fin.append(mapp[el])
    return fin

def a() -> None:
    parsed:{str:str} = parse()
    a = map_val(gen_map(chunk(parsed["seed-to-soil map"])[0], big(parsed["seeds"])), parsed["seeds"])
    b = map_val(gen_map(chunk(parsed["soil-to-fertilizer map"])[0], big(a)), a)
    c = map_val(gen_map(chunk(parsed["fertilizer-to-water map"])[0], big(b)), b)
    d = map_val(gen_map(chunk(parsed["water-to-light map"])[0], big(c)), c)
    e = map_val(gen_map(chunk(parsed["light-to-temperature map"])[0], big(d)), d)
    f = map_val(gen_map(chunk(parsed["temperature-to-humidity map"])[0], big(e)), e)
    return map_val(gen_map(chunk(parsed["humidity-to-location map"])[0], big(f)), f)

print(min([int(val) for val in a()]))
