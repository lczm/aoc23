import heapq
from typing import Dict, Tuple, List, Set
from pprint import pprint

with open("./input") as file:
    grid = []
    for line in file:
        grid.append(list(int(x) for x in line.strip()))

visited: Set[Tuple[int, int, int, int, int]] = set([])
# cost, row, col, dr, dc, steps
pq = [(0, 0, 0, 0, 0, 0)]


def add(queue, cost, row, col, dr, dc, steps=1):
    new_row = row + dr
    new_col = col + dc

    if not (0 <= new_row < len(grid) and 0 <= new_col < len(grid[new_row])):
        return

    heapq.heappush(
        queue,
        (
            cost + grid[new_row][new_col],
            new_row,
            new_col,
            dr,
            dc,
            steps,
        ),
    )


# part 1
# while pq:
#     cost, row, col, dr, dc, steps = heapq.heappop(pq)

#     # reached destination
#     if row == len(grid) - 1 and col == len(grid[row]) - 1:
#         print(cost)
#         break

#     # if we've seen it before, go next
#     if (row, col, dr, dc, steps) in visited:
#         continue

#     visited.add((row, col, dr, dc, steps))

#     if steps < 3 and (dr, dc) != (0, 0):
#         add(pq, cost, row, col, dr, dc, steps + 1)

#     for (
#         new_dr,
#         new_dc,
#     ) in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
#         if (new_dr, new_dc) != (dr, dc) and (new_dr, new_dc) != (-dr, -dc):
#             add(pq, cost, row, col, new_dr, new_dc)


while pq:
    cost, row, col, dr, dc, steps = heapq.heappop(pq)

    # reached destination
    if row == len(grid) - 1 and col == len(grid[row]) - 1:
        print(cost)
        break

    # if we've seen it before, go next
    if (row, col, dr, dc, steps) in visited:
        continue

    visited.add((row, col, dr, dc, steps))

    if steps < 10 and (dr, dc) != (0, 0):
        add(pq, cost, row, col, dr, dc, steps + 1)

    if steps >= 4 or (dr, dc) == (0, 0):
        for (
            new_dr,
            new_dc,
        ) in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            if (new_dr, new_dc) != (dr, dc) and (new_dr, new_dc) != (-dr, -dc):
                add(pq, cost, row, col, new_dr, new_dc)
