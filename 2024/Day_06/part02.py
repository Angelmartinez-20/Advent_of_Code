import numpy as np
import copy 

# makes numpy matrix of chars
with open('test.txt', 'r') as file:
    data = np.array([list(line.strip()) for line in file])

# find location of ^ (adjusted for numpy)
def init_loc(data):
    i, j = np.where(data == '^')
    return i[0], j[0]

# find marching path and returns num distinct positions
def find_path(i, j, data):
    dir = [1, 2, 3, 4]  # [up, right, down, left]
    dir_pos = 0
    steps = 0

    while(True):
        # going up
        if (dir_pos % len(dir)) == 0:
            for idx in range(i, -1, -1):
                steps += 1
                i = idx
                if data[i][j] == '.':
                    data[i][j] = 'X'
                elif data[i][j] == '#':
                    i += 1              # go back 1
                    break
            if i == 0: return 0
        # going right
        elif (dir_pos % len(dir)) == 1:
            for idx in range(j, len(data[i])):
                steps += 1
                j = idx
                if data[i][j] == '.':
                    data[i][j] = 'X'
                elif data[i][j] == '#':
                    j -= 1              # go back 1
                    break
            if j == len(data[i])-1: return 0
        # going down
        elif (dir_pos % len(dir)) == 2:
            for idx in range(i, len(data)):
                steps += 1
                i = idx
                if data[i][j] == '.':
                    data[i][j] = 'X'
                elif data[i][j] == '#':
                    i -= 1              # go back 1
                    break
            if i == len(data)-1: return 0
        # going left
        else:
            for idx in range(j, -1, -1):
                steps += 1
                j = idx
                if data[i][j] == '.':
                    data[i][j] = 'X'
                elif data[i][j] == '#':
                    j += 1              # go back 1
                    break
            if j == 0: return 0
        dir_pos += 1
        if steps > 10000: return 1 # I should use a better cycling detect algo

i, j = init_loc(data)
num_obsticles = 0

for idx in range(len(data)):
    for jdx in range(len(data[idx])):
        if data[idx][jdx] == '.':
            copy_data = copy.deepcopy(data)
            copy_data[idx][jdx] = '#'
            num_obsticles += find_path(i, j, copy_data)

print(num_obsticles)
