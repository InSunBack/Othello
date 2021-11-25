#include <iostream>

#include "Othello.h"

int main() {

    Othello *othello = new Othello();
    othello->Start();
    othello->Menu();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
