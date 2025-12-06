from constraint import *

def to_number(digits):
    sum = 0
    for i,digit in enumerate(digits):
        sum = sum * 10 + digit
    return sum

def get_sum(s, e, n, d, m ,o, r, y):
    send = to_number([s,e,n,d])
    more = to_number([m,o,r,e])
    money = to_number([m,o,n,e,y])
    return send + more == money


if __name__ == '__main__':
    problem = Problem(BacktrackingSolver())
    variables = ["S", "E", "N", "D", "M", "O", "R", "Y"]
    for variable in variables:
        problem.addVariable(variable, Domain(set(range(10))))

    # ---Tuka dodadete gi ogranichuvanjata----------------
    problem.addConstraint(AllDifferentConstraint(), variables)

    problem.addConstraint(get_sum, variables)
    # ----------------------------------------------------

    print(problem.getSolution())