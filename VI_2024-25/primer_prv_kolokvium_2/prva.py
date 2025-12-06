from searching_framework import *
from copy import deepcopy

# from utils import *
# from uninformed_search import *
# from informed_search import *

class Boxes(Problem):
    def __init__(self, initial, n, goal=None):
        super().__init__(initial, goal)
        self.size = n

    def actions(self, state):
        return self.successor(state).keys()

    def result(self, state, action):
        return self.successor(state)[action]

    def goal_test(self, state):
        return len(state[1]) == len(state[2])

    def successor(self, state):
        successors = {}
        player_pos = state[0]
        boxes = list(state[1])
        marked_boxes = list(state[2])
        moves = [(0,-1), (-1,0)]
        move_names = ["Dolu", "Levo"]
        for move,move_name in zip(moves, move_names):
            new_pos = (player_pos[0] + move[0], player_pos[1] + move[1])
            if new_pos not in boxes and 0 <= new_pos[0] and 0 <= new_pos[1]:
                new_marked_boxes = deepcopy(marked_boxes)
                for box in boxes:
                    if box not in new_marked_boxes and \
                            abs(box[0] - new_pos[0]) <= 1 and \
                            abs(box[1] - new_pos[1]) <= 1:
                        new_marked_boxes.append(box)
                successors[move_name] = (new_pos, tuple(boxes), tuple(new_marked_boxes))

        return successors


if __name__ == '__main__':
    n = int(input())
    man_pos = (n-1, n-1)

    num_boxes = int(input())
    boxes = list()
    for _ in range(num_boxes):
        boxes.append(tuple(map(int, input().split(','))))

    initial_state = (man_pos, tuple(boxes), tuple())
    p = Boxes(initial_state, n)
    solution = breadth_first_graph_search(p)
    print(solution.solution() if solution is not None else "No Solution!")
