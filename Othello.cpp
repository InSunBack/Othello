// Copyright 2021. Baek Insun

#include "Othello.h"
#include <list>
Othello::Othello() { }

void Othello::SetBoard() {
    int t;
    bool flag = true;
    int ascii = 65;
    // 최소 3칸이상 26칸 이하 Board 생성
    while (flag) {
        std::cin >> N;
        if (N < 3 || N > 26) {
            std::cout << " 잘못된 범위 입니다.";
        } else {
            flag = false;
        }
    }

    t = N / 2;

    matrix = new char*[N + 1];
    for (int i = 0; i <= N; i++) {
        matrix[i] = new char[N + 1];
    }



    for (int i = 1; i <= N; i++) {
        matrix[i][0] = static_cast<char>(ascii);
        matrix[0][i] = static_cast<char>(ascii);
        ascii++;
    }


    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            matrix[i][j] = '.';
        }
    }


    matrix[t][t] = 'B';
    matrix[t][t + 1] = 'W';
    matrix[t + 1][t] = 'W';
    matrix[t + 1][t + 1] = 'B';
}

void Othello::PrintBoard() {
    // 현재 Board 상태 출력
    std::cout << " ";
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Othello::Order(char Y, char X) {
    std::list<Dot*> ilist;
    char temp;
    char input;
    int y = (char)Y - 64;
    int x = (char)X - 64;

    if(matrix[y][x] != '.') {
        std::cout << "둘 수 없는 곳입니다." << std::endl;
        return;
    }
    //std::cout << y << x << std::endl;
    int length;
    if (turn) {
        input = 'B';
        temp = 'W';
    } else {
        input = 'W';
        temp = 'B';
    }


    for (auto & i : dydx) {
        int dy = i[0];
        int dx = i[1];
        //std::cout << " i : " << i << " ";
        int ny = y + dy;
        int nx = x + dx;
        bool flag = false;

        std::list<Dot*> tempList(ilist);
        // std::cout << "tempList size : " << ilist.size() << std::endl;

        while (true) {
            //  Board를 벗어난 경우
            if (ny < 1 || ny >= N || nx < 1 || nx >= N) {
                break;
            }

            char nowPoint = matrix[ny][nx];
            if (nowPoint == '.') {
                break;
            } else if (nowPoint == temp) {
                if (!flag) flag = true;
                tempList.push_front(new Dot(ny, nx));
            } else if (nowPoint == input) {
                if (flag) {
                    ilist = tempList;
                }
                break;
            }
            ny += dy;
            nx += dx;
        }
    }

    length = ilist.size();
    if (length == 0) {
        std::cout << "둘 수 없는 곳입니다." << std::endl;
        return;
    }

    if (turn) {
        turn = false;
    } else {
        turn = true;
    }

    for (int j = 0; j < length; j++) {
        int tempY = ilist.front()->y;
        int tempX = ilist.front()->x;
        ilist.pop_front();
        if (matrix[tempY][tempX] == input) {
            matrix[tempY][tempX] = temp;
        } else {
            matrix[tempY][tempX] = input;
        }
    }

    if (input == 'B') {
        matrix[y][x] = 'B';
    } else {
        matrix[y][x] = 'W';
    }
}

void Othello::PrintScore() const {
    int white_score_ = 0;
    int black_score_ = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            char temp = matrix[i][j];
            if (temp == 'W') {
                white_score_++;
            } else if (temp == 'B') {
                black_score_++;
            }
        }
    }
    std::cout << "White : "  << white_score_ << " Black : " << black_score_ << std::endl;
}

void Othello::Menu() {
    int command;
    bool flag = false;

    while(true) {
        std::cout << std::endl;
        std::cout << " 1 : Board 크기 설정 " << std::endl;
        std::cout << " 2 : 게임 시작 " << std::endl;
        std::cout << " 3 : 현재 점수 출력 " << std::endl;
        std::cout << " 4 : 게임 종료 " << std::endl;
        std::cin >> command;

        switch (command) {
            case 1:
                std::cout << "N x N Board를 생성합니다, N : ";
                SetBoard();
                Menu();
                break;
            case 2:
                while(true) {
                    char y;
                    char x;
                    PrintBoard();
                    std::cout << "좌표 입력 : " << std::endl;
                    std::cin >> y >> x;
                    if(y == '1' && x == '1') {
                        Menu();
                        break;
                    }
                    Order(y, x);
                }
            case 3:
                PrintScore();
                break;
            case 4:
                flag = true;
                break;
        }
        if(flag) {
            std::cout << "결과 : ";
            PrintScore();
            exit(0);
        }
        break;
    }

    return;
}

void Othello::Start() {
    std::cout << "     /////    ////////  //    //    //////    //        //      ///// " << std::endl;
    std::cout << "   //    //     //     //    //    //        //        //     //    //" << std::endl;
    std::cout << "  //     //    //     ////////    //////    //        //     //     //" << std::endl;
    std::cout << "  //    //    //     //    //    //        //        //      //    //" << std::endl;
    std::cout << "   /////     //     //    //    //////    //////    //////    /////" << std::endl;
    Menu();
}
