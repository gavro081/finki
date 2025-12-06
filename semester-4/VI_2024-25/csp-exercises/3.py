from constraint import *

def meeting_time_constraint(time, marija, petar):
    if time not in simona_domen or (marija and petar):
        return False
    if (marija and time in marija_domen) or (petar and time in petar_domen):
        return True

if __name__ == '__main__':
    problem = Problem(BacktrackingSolver())

    # ---Dadeni se promenlivite, dodadete gi domenite-----
    domain = range(12, 20)
    marija_domen = [14,15,18]
    simona_domen = [13,14,16,19]
    petar_domen = [12,13,16,17,18,19]
    problem.addVariable("Simona_prisustvo", [1])
    problem.addVariable("Marija_prisustvo", [0,1])
    problem.addVariable("Petar_prisustvo", [0,1])
    problem.addVariable("vreme_sostanok", domain)
    # ----------------------------------------------------

    # ---Tuka dodadete gi ogranichuvanjata----------------
    problem.addConstraint(meeting_time_constraint, ["vreme_sostanok", "Marija_prisustvo", "Petar_prisustvo"])

    # ----------------------------------------------------
    desired_order = ['Simona_prisustvo', 'Marija_prisustvo', 'Petar_prisustvo', 'vreme_sostanok']
    for solution in problem.getSolutions():
        ordered_solution = {key: solution[key] for key in desired_order}
        print(ordered_solution)
    # [print(solution) for solution in problem.getSolutions()]