import re
import numpy as np

with open('example.txt', 'r') as file:
    mem = file.read()

pattern = r"mul\((\d{1,3}),(\d{1,3})\)"

matches = np.array(re.findall(pattern, mem), dtype=int)
total = np.sum(np.prod(matches, axis=1))
print(total)
