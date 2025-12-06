from constraint import *

def overlap(*variables):
    for i in range(len(variables)):
        day1, time1 = variables[i].split("_")
        for j in range(i + 1, len(variables)):
            day2, time2 = variables[j].split("_")
            if day1 == day2 and (int(time1) - 1) <= int(time2) <= (int(time1) + 1):
                return False

    return True

def ml_constraint(*variables):
    day2, time2 = variables[-1].split("_")
    for ml_cas in variables:
        day1, time1 = ml_cas.split("_")
        if ml_cas == variables[-1]:
            return True
        if time1 == time2:
            return False
    # return True

if __name__ == '__main__':
    problem = Problem(BacktrackingSolver())
    casovi_AI = input()
    casovi_ML = input()
    casovi_R = input()
    casovi_BI = input()

    AI_predavanja_domain = ["Mon_11", "Mon_12", "Wed_11", "Wed_12", "Fri_11", "Fri_12"]
    ML_predavanja_domain = ["Mon_12", "Mon_13", "Mon_15", "Wed_12", "Wed_13", "Wed_15", "Fri_11", "Fri_12", "Fri_15"]
    R_predavanja_domain = ["Mon_10", "Mon_11", "Mon_12", "Mon_13", "Mon_14", "Mon_15", "Wed_10", "Wed_11", "Wed_12",
                           "Wed_13", "Wed_14", "Wed_15", "Fri_10", "Fri_11", "Fri_12", "Fri_13", "Fri_14", "Fri_15"]
    BI_predavanja_domain = ["Mon_10", "Mon_11", "Wed_10", "Wed_11", "Fri_10", "Fri_11"]

    AI_vezbi_domain = ["Tue_10", "Tue_11", "Tue_12", "Tue_13", "Thu_10", "Thu_11", "Thu_12", "Thu_13"]
    ML_vezbi_domain = ["Tue_11", "Tue_13", "Tue_14", "Thu_11", "Thu_13", "Thu_14"]
    BI_vezbi_domain = ["Tue_10", "Tue_11", "Thu_10", "Thu_11"]

    # ---Tuka dodadete gi promenlivite--------------------
    variables = []
    ml_variables = []
    for i in (range(int(casovi_AI))):
        var = f"AI_cas_{i+1}"
        variables.append(var)
        problem.addVariable(var, AI_predavanja_domain)
    for i in range(int(casovi_ML)):
        var = f"ML_cas_{i+1}"
        ml_variables.append(var)
        variables.append(var)
        problem.addVariable(var, ML_predavanja_domain)
    for i in range(int(casovi_R)):
        var = f"R_cas_{i+1}"
        variables.append(var)
        problem.addVariable(var, R_predavanja_domain)
    for i in range(int(casovi_BI)):
        var = f"BI_cas_{i+1}"
        variables.append(var)
        problem.addVariable(var, BI_predavanja_domain)

    ml_variables.append("ML_vezbi")
    vezbi_var = ["AI_vezbi", "ML_vezbi", "BI_vezbi"]
    variables += vezbi_var

    problem.addVariable("AI_vezbi", AI_vezbi_domain)
    problem.addVariable("ML_vezbi", ML_vezbi_domain)
    problem.addVariable("BI_vezbi", BI_vezbi_domain)
    # ---Tuka dodadete gi ogranichuvanjata----------------

    problem.addConstraint(AllDifferentConstraint(), variables)
    # vaka ne svetnuva zelena
    # problem.addConstraint(overlap, variables)

    # vaka raboti ne znam sto e razlikata
    for i in range(len(variables)):
        for j in range(i + 1, len(variables)):
            problem.addConstraint(overlap, (variables[i], variables[j]))
    problem.addConstraint(ml_constraint, ml_variables)


    # ----------------------------------------------------
    solution = problem.getSolution()

    print(solution)