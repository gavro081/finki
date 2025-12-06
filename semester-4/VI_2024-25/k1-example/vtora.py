from constraint import *


def no_neighboring_tents(*tent_variables):
    for tent1 in tent_variables:
        for tent2 in tent_variables:
            if tent1 == tent2:
                continue
            if abs(tent1[0] - tent2[0]) <= 1 and abs(tent1[1] - tent2[1]) <= 1:
                return False
    return True

def not_a_tree(*tent_variables):
    for tent in tent_variables:
        if tent in trees:
            return False
    return True


if __name__ == '__main__':
    problem = Problem(BacktrackingSolver())

    GRID_SIZE = 6
    # ----------------------------------------------------
    # ---Prochitajte gi informaciite od vlezot

    num_trees = int(input())
    trees = []
    for _ in range(num_trees):
        tree_x, tree_y = tuple(int(n) for n in input().split(" "))
        trees.append((tree_x, tree_y))

    # -----------------------------------------------------
    # ---Izberete promenlivi i domeni so koi bi sakale da rabotite-----

    variables = []
    for index, tree in enumerate(trees):
        tent_domain = []
        for i in [-1, 1]:
            new_x = tree[0] + i
            new_y = tree[1] + i
            if 0 <= new_x < GRID_SIZE:
                tent_domain.append((new_x, tree[1]))
            if 0 <= new_y < GRID_SIZE:
                tent_domain.append((tree[0], new_y))
        variable = f"tree{index}"
        variables.append(variable)
        problem.addVariable(variable, tent_domain)

    # -----------------------------------------------------
    # ---Potoa dodadete ogranichuvanjata-------------------
    problem.addConstraint(AllDifferentConstraint(), variables)
    problem.addConstraint(not_a_tree, variables)
    problem.addConstraint(no_neighboring_tents, variables)

    # -----------------------------------------------------
    # ---Potoa pobarajte reshenie--------------------------

    solution = problem.getSolution()

    # -----------------------------------------------------
    # ---Na kraj otpechatete gi poziciite na shatorite-----

    for i in range(num_trees):
        x, y = solution[f"tree{i}"]
        print(f"{x} {y}")

