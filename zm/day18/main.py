import sys
from typing import List, Tuple
from math import floor
from collections import deque


sys.setrecursionlimit(1000000000)


class Instruction:
    def __init__(self, direction: str, steps: int, hex_code: str):
        self.direction = direction
        self.steps = steps
        self.hex_code = hex_code[1 : len(hex_code) - 1]

    def swap(self):
        if self.hex_code[-1] == "0":
            self.direction = "R"
        elif self.hex_code[-1] == "1":
            self.direction = "D"
        elif self.hex_code[-1] == "2":
            self.direction = "L"
        elif self.hex_code[-1] == "3":
            self.direction = "U"
        self.steps = int(self.hex_code[1:6], 16)


instructions: List[Instruction] = []
with open("./input") as file:
    for line in file:
        direction, steps, hex_code = line.strip().split(" ")
        instructions.append(Instruction(direction, int(steps), hex_code))


for instruction in instructions:
    # part 2
    instruction.swap()
    print(instruction.direction, instruction.steps, instruction.hex_code)

max_length = sum([instruction.steps for instruction in instructions])
# grid = [["."] * max_length * 2 for i in range(max_length * 2)]

start: List[int] = [floor(max_length / 2), floor(max_length / 2)]
edges = [(start[0], start[1])]
perimeter = 0

for instruction in instructions:
    perimeter += instruction.steps
    if instruction.direction == "R":
        # for i in range(start[1], start[1] + instruction.steps + 1):
        #     grid[start[0]][i] = "#"
        start[1] += instruction.steps
    elif instruction.direction == "L":
        # for i in range(start[1], start[1] - instruction.steps - 1, -1):
        #     grid[start[0]][i] = "#"
        start[1] -= instruction.steps
    elif instruction.direction == "U":
        # for i in range(start[0], start[0] - instruction.steps - 1, -1):
        #     grid[i][start[1]] = "#"
        start[0] -= instruction.steps
    elif instruction.direction == "D":
        # for i in range(start[0], start[0] + instruction.steps + 1):
        #     grid[i][start[1]] = "#"
        start[0] += instruction.steps
    edges.append((start[0], start[1]))


def part1():
    walls = 0
    for row in grid:
        for col in row:
            if col == "#":
                walls += 1

    def flood(grid, x, y):
        if grid[x][y] != ".":
            return
        queue = deque([(x, y)])
        rows, cols = len(grid), len(grid[0])
        while queue:
            xx, yy = queue.popleft()
            if grid[xx][yy] == ".":
                grid[xx][yy] = "#"
                for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    nx, ny = xx + dx, yy + dy
                    if 0 <= nx < rows and 0 <= ny < cols:
                        queue.append((nx, ny))

    flood(grid, 0, 0)
    insides = 0
    for row in grid:
        for col in row:
            if col == ".":
                insides += 1

    print(walls + insides)


min_x = 100000000
min_y = 100000000
for edge in edges:
    min_x = min(edge[0], min_x)
    min_y = min(edge[1], min_y)

e = []
for edge in edges:
    e.append((edge[0] - min_x, edge[1] - min_y))

for edge in e:
    print(edge)

e = list(reversed(e))


# wikipedia example for shoelace - check that it's 16.5
# e = [(1, 6), (3, 1), (7, 2), (4, 4), (8, 5), (1, 6)]


def part2():
    # shoelace the edges together
    cumulative = 0
    for i in range(len(e) - 1):
        left, right = e[i], e[i + 1]
        # print(left, right)
        ll = left[0] * right[1]
        rr = left[1] * right[0]
        det = ll - rr
        cumulative += det

    print((cumulative / 2) + (perimeter / 2 + 1))


# part1()
part2()
