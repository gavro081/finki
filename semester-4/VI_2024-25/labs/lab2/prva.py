from searching_framework import Problem, astar_search

class House(Problem):
    def __init__(self, initial, player_allowed, house_allowed, goal=None):
        super().__init__(initial, goal)
        self.player_allowed = player_allowed
        self.house_allowed = house_allowed

    def successor(self, state):
        """
        :param state: (player_pos, house_pos, house_dir)
        :return: „Stoj/Gore 1/Gore 2/Gore-desno 1/Gore-desno 2/Gore-levo 1/Gore-levo 2“
        """
        player_pos = list(state[0])
        house_pos = list(state[1][0])
        house_dir = state[1][1][0]
        successors = {}
        moves = [(0,0), (0,1), (0,2), (1,1), (2,2), (-1, 1), (-2, 2)]
        move_names = ["Stoj","Gore 1", "Gore 2","Gore-desno 1","Gore-desno 2","Gore-levo 1","Gore-levo 2"]
        # print(state)
        if house_dir == 'l':
            if house_pos[0] == 0:
                new_house_pos = ((1,8), tuple("r"))
            else:
                new_house_pos = ((house_pos[0] - 1, 8), tuple(house_dir))
        else:
            if house_pos[0] == 4:
                new_house_pos = ((3,8), tuple("l"))
            else:
                new_house_pos = ((house_pos[0] + 1, 8), tuple(house_dir))

        for move, move_name in zip(moves, move_names):
            new_player_pos = (player_pos[0] + move[0], player_pos[1] + move[1])
            if new_player_pos in self.player_allowed or new_player_pos == new_house_pos[0]:
                successors[move_name] = (new_player_pos, new_house_pos)

        return successors

    def actions(self, state):
        return self.successor(state).keys()

    def result(self, state, action):
        return self.successor(state)[action]

    def goal_test(self, state):
        return state[0] == state[1][0]

    def h(self, node):
        state = node.state
        player_x, player_y = state[0]
        house_x, house_y = state[1][0]
        return (abs(player_x - house_x) + abs(player_y - house_y)) / 7


if __name__ == '__main__':
    allowed = [(1, 0), (2, 0), (3, 0), (1, 1), (2, 1), (0, 2), (2, 2), (4, 2), (1, 3), (3, 3), (4, 3), (0, 4), (2, 4),
               (2, 5), (3, 5), (0, 6), (2, 6), (1, 7), (3, 7)]
    house_allowed = [(8,0), (8,1), (8,2), (8,3), (8,4)] # valjda
    player_start_pos = tuple([int(n) for n in input().split(",")])
    house_start_pos = tuple([int(n) for n in input().split(",")])
    house_dir = 'r' if input() == "desno" else 'l'
    initial_state = (player_start_pos, (house_start_pos, tuple(house_dir)))
    p = House(initial_state, allowed, house_allowed)
    solution = astar_search(p)
    print(solution.solution() if solution is not None else [])

    # your code here