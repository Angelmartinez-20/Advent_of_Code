import re
import numpy as np

with open('test.txt', 'r') as file:
    mem = file.read()

clean_mem = ''
i = 0
do_block = True 

# iterates through memory string to only include 'do' parts
while i < len(mem):
    if do_block:
        if mem[i:i+5] == "don't":
            do_block = False 
            i += 5
        else:
            clean_mem+=mem[i]
            i += 1
    else:
        if mem[i:i+2] == 'do' and mem[i:i+5] != "don't":
            do_block = True 
            i += 2
        else:
            i += 1


pattern = r"mul\((\d{1,3}),(\d{1,3})\)"

matches = np.array(re.findall(pattern, clean_mem), dtype=int)
total = np.sum(np.prod(matches, axis=1))
print(total)