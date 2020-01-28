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
    if (square == Square::FREE) {
        out << '-';
    }
    else if (square == Square::WHITE) {
        out << 'W';
    }
    else {
        out << 'B';
    }
    return out;
}

Square::SquareValue opposite_color(Square::SquareValue value) {
    if (value == Square::WHITE) {
        return Square::BLACK;
    }
    else if (value == Square::BLACK) {
        return Square::WHITE;
    }
    return Square::FREE;
}

std::ostream& operator<<(std::ostream& out, const Board& board) {
    if (board.dimension_ > 10) {
        cout << "  ";
        for (int i=0; i<board.dimension_; i++) {
            if (i > 10) {
                cout << i/10;
            }
            else {
                cout << ' ';
            }
        }
        cout << std::endl;
    }
    cout << "  ";
    for (int i=0; i<board.dimension_; i++) {
        cout << i%10;
    }
    cout << std::endl;
    for (int i=0; i<board.dimension_; i++) {
        cout << ('a'+i) << ':';
        for (int j=0; j<board.dimension_; j++) {
            cout << board.squares_[i][j];
        }
        cout << std::endl;
    }
    cout << std::endl;
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

