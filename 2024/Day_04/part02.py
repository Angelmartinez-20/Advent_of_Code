import csv
import numpy as np

# reads data into lists of lists
with open('test.txt', 'r') as file:
    data = [list(line.strip()) for line in file]

num_finds = 0
first_diag = [(-1,-1), (1,1)]   # upper left, lower right \
second_diag = [(1,-1),(-1,1)]   # lower left, upper right /

def find_mas(i, j, diag):
    next_i = i+diag[0][0]
    next_j = j+diag[0][1]

    # check if in bounds
    if ((next_i >= 0 and next_i < len(data)) and (next_j >= 0 and next_j < len(data))):
        if(data[next_i][next_j] == "M"):
            next_i = i+diag[1][0]
            next_j = j+diag[1][1]
            # check if in bounds
            if((next_i >= 0 and next_i < len(data)) and (next_j >= 0 and next_j < len(data))):
                if(data[next_i][next_j] == "S"): 
                    return True
                else: return False
            else: return False
        elif(data[next_i][next_j] == "S"):
            next_i = i+diag[1][0]
            next_j = j+diag[1][1]
            # check if in bounds
            if ((next_i >= 0 and next_i < len(data)) and (next_j >= 0 and next_j < len(data))):
                if(data[next_i][next_j] == "M"):
                    return True
                else: return False
            else: return False
        else: return False
    return False
    

# compares each possible directions
def find_x(i, j):
    global num_finds
    if (find_mas(i, j, first_diag) and find_mas(i, j, second_diag)):
        num_finds += 1


# iters through data looking center "A"
for i, row in enumerate(data):
    for j, val in enumerate(row):
        if val == "A":
            find_x(i, j)

print(num_finds)