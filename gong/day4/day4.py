def parser() -> [[str]]:
    with open("input2","r") as fhand:
        t:[[str]] = [line.strip().split("|") for line in fhand]
    return [(el[0].split(":")[0].lstrip("Card "), el[0].split(":")[1].strip().split(" "), el[1].strip().split(" ")) for el in t]

def sanitise(parsed:[[str]]) -> [[int]]:
    return [([int("".join(el[0]))], [int(i) for i in el[1] if i != ""], [int(q) for q in el[2] if q != ""]) for el in parsed]

def check(win:[int],urs:[int]) -> int:
    fin:int = 0
    for val in urs:
        if val in win:
            fin += 1
    return fin

def a() -> int:
    tot:[float] = []
    parsed:[[int]] = sanitise(parser())
    for game in parsed:
        tem:float = 0.5
        for i in range(check(game[1],game[2])):
            tem = tem * 2
        if tem != 0.5:
            tot.append(int(tem))
    return sum(tot)

def b() -> int:
    stor:{str:int} = {}
    parsed:[[int]] = sanitise(parser())
    for game in parsed:
        rep = 1
        if str(game[0][0]) in stor:
            rep = stor[str(game[0][0])]
        for i in range(game[0][0], game[0][0] + 1 + check(game[1],game[2])):
            stor[str(i)] = stor.get(str(i),0) + rep
    return sum([stor[val] for val in stor])

print(a())
print(b())
