def atupalau() -> [{str:int}]:
    with open("input","r") as fhand:
        val:[int] = []
        for pair in [line.rstrip().split(":") for line in fhand]:
            game_num = int(pair[0].lstrip("Game "))
            count = {}
            for q in [set.split(",") for set in pair[1].split(";")]:
                for s in q:
                    count["NUM"] = game_num
                    if s.endswith(" green"):
                        if "G" in count:
                            if int(s.rstrip(" green")) > count["G"]:
                                count["G"] = int(s.rstrip(" green"))
                        else:
                            count["G"] = int(s.rstrip(" green"))
                    elif s.endswith(" red"):
                        if "R" in count:
                            if int(s.rstrip(" red")) > count["R"]:
                                count["R"] = int(s.rstrip(" red"))
                        else:
                            count["R"] = int(s.rstrip(" red"))
                    elif s.endswith(" blue"):
                        if "B" in count:
                            if int(s.rstrip(" blue")) > count["B"]:
                                count["B"] = int(s.rstrip(" blue"))
                        else:
                            count["B"] = int(s.rstrip(" blue"))
            val.append(count)
    return val

def a() -> int:
    parsed:[{str:int}]= atupalau()
    return sum([el["NUM"] for el in parsed if el["R"] <= 12 and el["B"] <= 14 and el["G"] <= 13])

def b() -> int:
    parsed:[{str:int}]= atupalau()
    return sum([el["R"] * el["B"] * el["G"] for el in parsed])

print(a())
print(b())
