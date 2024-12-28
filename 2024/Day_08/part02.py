from itertools import permutations

# reads data into matrix
with open("test.txt", "r") as file:
    data = [line.strip() for line in file]

# create map as dictinary using compelex number as map indecies
def construct_map(data):
    map = {}
    for i, row in enumerate(data):
        for j, chr in enumerate(row):
            map[i + j * 1j] = chr
    return map

def calculate_antinodes(map):
    antinodes = []
    frequencies = {*map.values()} - {'.'}

    for freq in frequencies:
        antennas = []
        for p in map:
            if map[p] == freq: antennas.append(p)
        pairs = permutations(antennas, 2)
        for a, b in pairs:
            for n in range(50):
                antinodes.append(a + n * (a - b))

    return len(set(antinodes) & set(map))

map = construct_map(data)
result = calculate_antinodes(map)
print(result)