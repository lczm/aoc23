def a(filename:str) -> int:
    with open(filename, "r") as fhand:
        fin:[[int]]= [[int(char) for char in line if char.isnumeric()] for line in (line.rstrip() for line in fhand)]
    return sum(int(str(val[0]) + str(val[-1])) if len(val) > 1 else int(str(val[0]) * 2) for val in fin)

def b() -> int:
    valid = {"one": "1", "two": "2", "three": "3", "four": "4", "five": "5", "six": "6", "seven": "7", "eight": "8", "nine": "9"}
    with open("input", "r") as fhand:
        fin = '\n'.join(''.join(char if char.isnumeric() else next(valid[word] for word in valid if word in buf) if buf else '' for buf, char in zip([''] + line, line)) for line in [line.rstrip() for line in fhand])
    with open("temp", "w") as fhand:
        fhand.write(fin.rstrip())
    return a("temp")

print(a("input"))
print(b())
