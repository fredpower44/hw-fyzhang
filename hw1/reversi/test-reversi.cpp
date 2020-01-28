#include <iostream>
#include <cstdlib>

#include "reversi.h"

using namespace std;


/**
 * main - Entry point for Reversi
 *  should create a Reversi object using the dimension
 *  provided as the 1st command line argument, or, if
 *  no argument is provided, default to 4.
 *  Once created, call Reversi::play() on the Reversi
 *  object and then return 0;
 */

std::ostream& operator<<(std::ostream& out, const Square& square) {
    if (square_== 0) {
        out << '-';
    }
    else if (square == WHITE) {
        out << 'W';
    }
    else {
        out << 'B';
    }
    return out;
}

int main(int argc, char* argv[])
{
    size_t size = 4;
    if (argc >= 2)
    {
        size = atoi(argv[1]);
        if( ((size % 2) == 1) ||
                ((size < 4) || (size > 26)) ) {
            cout << "Invalid size" << endl;
            return 1;
        }
        else {
            size = atoi(argv[1]);
        }
    }
    Reversi game(size);
    game.play();
    return 0;
}

