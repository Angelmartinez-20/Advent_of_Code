import numpy as np

# read data from file
data = np.loadtxt('test.txt').astype(int)
left_col = data[:, 0]  
right_col = data[:, 1]

# calculates total distance
left_col = np.sort(left_col)
right_col = np.sort(right_col)
total_dist = abs(left_col - right_col)

print(np.sum(total_dist))