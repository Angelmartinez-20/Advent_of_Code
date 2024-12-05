import numpy as np
import csv

def is_safe(row):
    is_increm = row[0] < row[1]

    for i in range(1, len(row)):
        dist = abs(row[i] - row[i-1])
        if dist < 1 or dist > 3: return False
        # checks if entire row either increminting or decrementing
        if (is_increm and row[i] < row[i-1]) or (not is_increm and row[i] > row[i-1]):
            return False
        
    return True

# reads data into lists of lists
data = []
with open('test.txt', 'r') as file:
    reader = csv.reader(file, delimiter=' ')
    for row in reader:
        data.append([int(val) for val in row])

# calculates number of safe rows
num_saves = 0
for row in data:
    if is_safe(row): num_saves += 1

print(num_saves)
