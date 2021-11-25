// Copyright 2021. Group 7

#ifndef _HOME_XEHA_OTHELLO_OTHELLO_H_
#define _HOME_XEHA_OTHELLO_OTHELLO_H_

#include <iostream>

class Dot {
public:
    int y;
    int x;
    Dot(int y, int x) {
        this->y = y;
        this->x = x;
    }
};

class Othello {
public:
    Othello();
    void Start();
    void Menu();
    void SetBoard();
    void PrintBoard();
    void PrintScore() const;
    void Order(char y, char x);

    bool turn = true;
    char** matrix;
    int N;
    int dydx[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}
            , {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
private:
};

#endif  // _HOME_XEHA_OTHELLO_OTHELLO_H_