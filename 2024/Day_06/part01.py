import numpy as np

# makes numpy matrix of chars
with open('test.txt', 'r') as file:
    data = np.array([list(line.strip()) for line in file])

# find location of ^
def init_loc(data):
    i, j = np.where(data == '^')
    return i[0], j[0]


# find marching path and returns num distinct positions
def find_path(i, j, data):
    distinct_pos = 0
    dir = [1, 2, 3, 4]  # [up, right, down, left]
    dir_pos = 0

    while(True):
        # going up
        if (dir_pos % len(dir)) == 0:
            for idx in range(i, -1, -1):
                i = idx
                if data[i][j] == '.':
                    data[i][j] = 'X'
                    distinct_pos += 1
                elif data[i][j] == '#':
                    i += 1              # go back 1
                    break
            if i == 0: return distinct_pos
        # going right
        elif (dir_pos % len(dir)) == 1:
            for idx in range(j, len(data)):
                j = idx
                if data[i][j] == '.':
                    data[i][j] = 'X'
                    distinct_pos += 1
                elif data[i][j] == '#':
                    j -= 1              # go back 1
                    break
            if j == len(data)-1: return distinct_pos
        # going down
        elif (dir_pos % len(dir)) == 2:
            for idx in range(i, len(data)):
                i = idx
                if data[i][j] == '.':
                    data[i][j] = 'X'
                    distinct_pos += 1
                elif data[i][j] == '#':
                    i -= 1              # go back 1
                    break
            if i == len(data)-1: return distinct_pos
        # going left
        else:
            for idx in range(j, -1, -1):
                j = idx
                if data[i][j] == '.':
                    data[i][j] = 'X'
                    distinct_pos += 1
                elif data[i][j] == '#':
                    j += 1              # go back 1
                    break
            if j == 0: return distinct_pos
        dir_pos += 1

i, j = init_loc(data)
distinct_pos = find_path(i, j, data)
print(distinct_pos+1)
