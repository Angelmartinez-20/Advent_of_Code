

def read_file(rules, updates):
    with open('test.txt', 'r') as file:
        data = file.read()

    sections = data.strip().split('\n\n')

    # create dict where right values must not come before left values
    first_section = sections[0].splitlines()
    for line in first_section:
        left, right = line.split('|')
        left, right = int(left), int(right)
        if right not in rules:
            rules[right] = []
        rules[right].append(left)

    second_section = sections[1].splitlines()
    for line in second_section:
        row = list(map(int, line.split(',')))
        updates.append(row)

def right_order(row, rules):
    fixed_row = False
    for i in range(len(row)-1):
        for j in range(i+1, len(row)):
            if row[i] in rules and row[j] in rules[row[i]]:
                row[i], row[j] = row[j], row[i]
                fixed_row = True
    if fixed_row:
        return row[len(row) // 2]
    else:
        return 0

rules = {}
updates = []
middle_sum = 0
read_file(rules, updates)

for row in updates:
    middle_sum += right_order(row, rules)
                
print(middle_sum)