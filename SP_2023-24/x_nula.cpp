//
// Created by Filip on 29.12.24.
//
#include <iostream>

void printBoard();
bool compare(char a);
bool checkMove(int move);
bool isGameOver();

using namespace std;
char grid[3][3];

int main() {
    int move, moves = 0;
    int ctr = '0';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = ++ctr;
        }
    }
    char playerSymbol[2] = {'x', '0'}, ans;
    cout << "Choose Player 1's symbol (x/0):";
    cin >> ans;
    if (ans == '0') swap(playerSymbol[0],playerSymbol[1]);
    printBoard();
    int currPlayer=2;
    while (true) {
        currPlayer = (currPlayer==1) ? 2 : 1;
        do {
            cout << "Player " << currPlayer << "'s move:";
            cin >> move;
            move--;
        } while (checkMove(move));
        grid[move / 3][move % 3] = playerSymbol[currPlayer-1];
        moves++;
        printBoard();
        if (isGameOver() || moves == 9) break;
    }
    if (isGameOver()) cout << "\nPlayer " << currPlayer << " WON!\n";
    else cout<<"\nIT'S A TIE!";
}

void printBoard() {
    cout<<'\n';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << grid[i][j];
            if (j != 2) cout << " | ";
        }
        cout << '\n';
    }
}
bool compare(char a) {
    if (a == 'x' || a == '0') return true;
    else return false;
}
bool checkMove(int move) {
    char a;
    a = grid[move / 3][move % 3];
    return compare(a);
}
bool isGameOver() {
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]) return true;
        if (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i]) return true;
    }
    if (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]) return true;
    if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) return true;
    return false;
}