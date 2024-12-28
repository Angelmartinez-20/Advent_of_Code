import numpy as np

# reads in data from file
with open("test.txt", "r") as file:
    data = np.array(list(file.read()), dtype=int)
    # adds 0 to last file with NO partitions after
    if len(data) % 2 != 0:
        data = np.append(data, 0)

# create partition map of harddrive
def harddrive_map(paired_files):
    harddrive = []
    id_val = 0

    for pair in paired_files:
        harddrive.extend([id_val] * pair[0])
        harddrive.extend([-1] * pair[1])
        id_val += 1

    return harddrive

# shifts far right files to furthest empty left
def optimize_space(harddrive):
    opt_harddrive = []
    left_ptr = 0
    right_ptr = len(harddrive) - 1

    while (left_ptr <= right_ptr):
        if (harddrive[left_ptr] != -1):
            opt_harddrive.append(harddrive[left_ptr])
        # empty partition
        else:
            # find furthest right file (non empty)
            while harddrive[right_ptr] == -1: 
                right_ptr -= 1
            if (left_ptr < right_ptr):
                opt_harddrive.append(harddrive[right_ptr])
            right_ptr -= 1
        left_ptr += 1
        
    return opt_harddrive

def calculate_checksum(opt_harddrive):
    checksum = 0
    for idx, val in enumerate(opt_harddrive):
        checksum += idx * val
    return checksum

paired_files = data.reshape(-1, 2)          # pairs 1st and 2nd elements together
harddrive = harddrive_map(paired_files)
opt_harddrive = optimize_space(harddrive)
checksum = calculate_checksum(opt_harddrive)
print(checksum)

