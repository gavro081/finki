//
// Created by Filip on 29.12.24.
//
zajak zadaca kolok:
#include <iostream>

using namespace std;

void makeMoveHelper(int &playerX, int &playerY, int direction);

void makeMove(int &playerX, int &playerY, char move, int &direction);

bool isGameOver(int playerX, int playerY, int n, int m, int k, int l);

void printBoard(int playerX, int playerY, int n, int m, int k, int l);

int main() {
    int n, m;
    cin >> n >> m;
    int k, l;
    cin >> k >> l;
    char move;
    int playerX, playerY, direction, moves;
    moves = direction = 0;
    playerX = n - 1;
    playerY = m - 1;
    while (cin >> move) {
        makeMove(playerX, playerY, move, direction);
        if (isGameOver(playerX, playerY, n, m, k, l)) break;
        moves++;
        if (moves == 1e3) {
            cout << "GAMEOVER\n";
            break;
        }
//        printBoard(playerX,playerY,n,m,k,l);
    }
}

void makeMoveHelper(int &playerX, int &playerY, int direction) {
    switch (direction) {
        case 0:
            playerX--;
            break;
        case 1:
            playerY++;
            break;
        case 2:
            playerX++;
            break;
        case 3:
            playerY--;
            break;
    }
}

void makeMove(int &playerX, int &playerY, char move, int &direction) {
    switch (move) {
    case 'J' : case 'j':
            break;
            case 'L': case 'l':
            direction += 3;
            direction = abs(direction % 4);
            break;
            case 'R': case 'r':
            direction++;
            direction = abs(direction % 4);
            break;
        default: return;
    }
    makeMoveHelper(playerX,playerY,direction);
}

bool isGameOver(int playerX, int playerY, int n, int m, int k, int l) {
    if (playerX == k && playerY == l) {
        cout << "NJAM!\n";
        return true;
    }
    if (playerX < 0 || playerX >= n || playerY < 0 || playerY >= m) {
        cout << "GAME OVER Fence.\n";
        return true;
    } else return false;
}

void printBoard(int playerX, int playerY, int n, int m, int k, int l) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == playerX && j == playerY) cout << "X ";
            else if (i == k && j == l) cout << "C ";
            else cout << "0 ";
        }
        cout << '\n';
    }
}
