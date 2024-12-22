import itertools

data = []

# reads data into list of pairs 
with open('test.txt', 'r') as file:
    for line in file:
        left, right = line.split(': ')
        target = int(left)
        numbers = list(map(int, right.split()))
        problem = (target, numbers)
        data.append(problem)

# evaluates expression left to right
def evaluate(problem, operators):
    target = problem[0]
    numbers = problem[1]
    result = numbers[0]   

    # applies combination of operators to results       
    for i in range(1, len(numbers)):
        operator = operators[i-1]
        if operator == '+':
            result += numbers[i]
        elif operator == '*':
            result *= numbers[i]
        elif operator == '||':
            result = int(str(result) + str(numbers[i]))
    
    return result == target

# generate and checks each combinations
def check_equations(problem):
    OPERATORS = ['+', '*', '||']
    # makes every combination of operators
    for ops in itertools.product(OPERATORS, repeat=len(problem[1])-1):
        if evaluate(problem, ops):
            return True
    return False

results = []
for problem in data:
    if check_equations(problem):
        results.append(problem[0])

print(sum(results))
