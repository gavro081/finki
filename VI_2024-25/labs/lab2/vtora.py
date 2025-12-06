from searching_framework import Problem, astar_search

class House(Problem):
    def __init__(self, initial, house_pos, walls, goal=None):
        super().__init__(initial, goal)
        self.house_pos = house_pos
        self.walls = walls

    def successor(self, state):
        player_pos = state
        moves = [(0,1), (0, -1), (-1, 0)]
        move_names = ["Gore", "Dolu", "Levo"]
        successors = {}
        for move, move_name in zip(moves, move_names):
            new_move = (player_pos[0] + move[0], player_pos[1] + move[1])
            if new_move not in self.walls and 0 <= new_move[0] < n and 0 <= new_move[1] < n:
                successors[move_name] = new_move
        if (player_pos[0] + 1, player_pos[1]) not in self.walls:
            for i in [2,3]:
                new_move = (player_pos[0] + i, player_pos[1])
                if new_move not in self.walls and 0 <= new_move[0] < n and 0 <= new_move[1] < n:
                    successors[f"Desno {i}"] = new_move
                else:
                    break

        return successors

    def actions(self, state):
        return self.successor(state).keys()

    def result(self, state, action):
        return self.successor(state)[action]

    def goal_test(self, state):
        return state == self.house_pos

    def h(self, node):
        player_pos = node.state
        return (abs(player_pos[0] - self.house_pos[0]) + abs(player_pos[1] - self.house_pos[1]))/6

if __name__ == '__main__':
    n = int(input())
    num_walls = int(input())
    walls = []
    for _ in range(num_walls):
        x,y = input().split(",")
        walls.append((int(x), int(y)))
    player_start_pos = tuple([int(n) for n in input().split(",")])
    house_pos = tuple([int(n) for n in input().split(",")])
    p = House(player_start_pos, house_pos, walls)
    solution = astar_search(p)
    print(solution.solution() if solution is not None else [])
