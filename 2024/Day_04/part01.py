import csv
import numpy as np

# reads data into lists of lists
with open('test.txt', 'r') as file:
    data = [list(line.strip()) for line in file]

xmas = "XMAS"
num_finds = 0

# 8 possible search dirations
possible_dir = [(0,1),(1,1), (1,0), (1,-1), (0,-1), (-1,-1), (-1,0), (-1,1)]

#
def compare_word(i, j, dir):
    global num_finds
    # checks rest of word ["M","A","S"]
    for char_itr in range(1, len(xmas)):
        next_i, next_j = i + char_itr * dir[0], j + char_itr * dir[1]
        # check if position no out of bounds or !match word
        if ((next_i < 0 or next_i >= len(data)) or 
            (next_j < 0 or next_j >= len(data[next_i])) or
            data[next_i][next_j] != xmas[char_itr]):
            return
    num_finds += 1


# compares each possible directions
def find_word(i, j):
    for dir in possible_dir:
        compare_word(i, j, dir)

# iters through data looking for "X"
for i, row in enumerate(data):
    for j, val in enumerate(row):
        if val == xmas[0]:
            find_word(i, j)

print(num_finds)