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
    file_dict = {}
    id_val = 0

    for pair in paired_files:
        harddrive.extend([id_val] * pair[0])
        harddrive.extend([-1] * pair[1])
        file_dict[id_val] = pair[0]
        id_val += 1
        

    return harddrive, file_dict, id_val-1

def num_consecutive_space(harddrive, itr):
    consecutive_count = 0
    for i in range(itr, len(harddrive)):
        if harddrive[i] != -1: break
        consecutive_count += 1 
    return consecutive_count

# shifts far right files to furthest empty left
def optimize_space(harddrive, file_dict, largest_id):
    desc_id = largest_id

    while(desc_id > 0):
        i = 0
        while (i < len(harddrive)):
            if harddrive[i] == desc_id: break
            if harddrive[i] == -1:
                num_space = num_consecutive_space(harddrive, i)
                if num_space < file_dict[desc_id]:
                    i += 1
                    continue
                else:
                    val_loc = harddrive.index(desc_id)
                    for idx in range(file_dict[desc_id]):
                        harddrive[i+idx], harddrive[val_loc+idx] = harddrive[val_loc+idx], harddrive[i+idx]
                    break
            i += 1
        desc_id -= 1


def calculate_checksum(opt_harddrive):
    checksum = 0
    for idx, val in enumerate(opt_harddrive):
        if val == -1: checksum += idx * 0
        else: checksum += idx * val
    return checksum

paired_files = data.reshape(-1, 2)          # pairs 1st and 2nd elements together
harddrive, file_dict, largest_id = harddrive_map(paired_files)
optimize_space(harddrive, file_dict, largest_id)
checksum = calculate_checksum(harddrive)
print(checksum)

