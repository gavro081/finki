import random
import os
from random import choice, randint

os.environ["OPENBLAS_NUM_THREADS"] = "1"
random.seed(0)


class Player:
    def __init__(self):
        self.col = 0
        self.row = 0

    def move(self, position):
        self.row = position[0]
        self.col = position[1]
        print(f"[{self.row}, {self.col}]")


class Game:
    def __init__(self, table, n, m):
        self.table = table
        self.width = n
        self.height = m
        self.dots = sum(row.count('.') for row in table)

    def print_table(self):
        for i in range(self.width):
            print(self.table[i])


class Pacman:
    def __init__(self, player, game):
        self.player = player
        self.game = game

    def get_valid_moves(self):
        valid_moves = []
        for i in (-1, 1):
            new_row = self.player.row + i  # gore dole
            new_col = self.player.col + i  # levo desno
            if 0 <= new_row < self.game.height:  # gore dole
                valid_moves.append((new_row, self.player.col))
            if 0 <= new_col < self.game.width:  # levo desno
                valid_moves.append((self.player.row, new_col))
        return valid_moves

    def get_surrounding_dots(self, valid_moves):
        return [(row, col) for row, col in valid_moves if self.game.table[row][col] == '.']

    def mark_dot(self, move):
        self.game.table[move[0]][move[1]] = '#'

    def play_game(self):
        # self.game.print_table()
        if self.game.dots == 0:
            print("Nothing to do here")
            return
        while True:
            valid_moves = self.get_valid_moves()
            dots = self.get_surrounding_dots(valid_moves)
            if len(dots) > 0:
                next_move = choice(dots)
                # next_move = dots[randint(0, len(dots) - 1)]
                self.mark_dot(next_move)
                self.player.move(next_move)
                self.game.dots -= 1
                if self.game.dots <= 0:
                    break
            else:
                next_move = choice(valid_moves)
                # next_move = valid_moves[randint(0, len(valid_moves) - 1)]
                self.player.move(next_move)

            # self.game.print_table()
            # print()


if __name__ == "__main__":
    n = int(input())  # width
    m = int(input())  # height
    start_table = []
    for i in range(n):
        start_table.append(list(input()))

    p = Player()
    g = Game(start_table, n, m)
    pacman = Pacman(p, g)
    pacman.play_game()