from sys import stdin

ws = list(len(set.intersection(*(set(map(int, xs.split())) for xs in line.rstrip().split(': ')[1].split(' | ')))) for line in stdin)
ns = [1] * len(ws)
for i, w in enumerate(ws):
    for j in range(i + 1, i + w + 1):
        ns[j] += ns[i]
print(sum(ns))