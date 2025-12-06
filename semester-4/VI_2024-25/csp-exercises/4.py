from constraint import *

if __name__ == '__main__':
    num = int(input())

    papers = dict()

    paper_info = input()
    while paper_info != 'end':
        title, topic = paper_info.split(' ')
        papers[title] = topic
        paper_info = input()

    # Tuka definirajte gi promenlivite
    variables = []
    ai_variables = []
    ml_variables = []
    nlp_variables = []
    for paper in papers:
        type = papers[paper]
        var = f"{paper} ({type})"

        if type == "AI": ai_variables.append(var)
        elif type == "ML": ml_variables.append(var)
        else: nlp_variables.append(var)

        variables.append(var)

    domain = [f'T{i + 1}' for i in range(num)]
    problem = Problem(BacktrackingSolver())

    # Dokolku vi e potrebno moze da go promenite delot za dodavanje na promenlivite
    problem.addVariables(variables, domain)

    # Tuka dodadete gi ogranichuvanjata

    def all_in_one_constraint(*vars):
        if len(vars) <= 4:
            rep = vars[0]
            for i in vars:
                if i != rep:
                    return False
        return True

    def max_per_slot_constraint(*vars):
        count = {}
        for var in vars:
            count[var] = count.get(var,0) + 1
            if count[var] > 4:
                return False
        return True

    problem.addConstraint(all_in_one_constraint, ai_variables)
    problem.addConstraint(all_in_one_constraint, nlp_variables)
    problem.addConstraint(all_in_one_constraint, ml_variables)
    problem.addConstraint(max_per_slot_constraint, variables)

    result = problem.getSolution()

    # Tuka dodadete go kodot za pechatenje

    for key, val in sorted(result.items(), key=lambda x: int(x[0].split()[0][5:])):
        print(f'{key}: {val}')
