import numpy as np
from collections import Counter

# read data from file
data = np.loadtxt('test.txt').astype(int)
left_col = data[:, 0]  
right_col = data[:, 1]

# calculates similarity_score
right_occurs = Counter(right_col)   
similarity_score = [(i * right_occurs[i]) for i in left_col]

print(np.sum(similarity_score))
