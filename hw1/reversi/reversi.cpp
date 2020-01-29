#include <vector>
#include <stdexcept>

#include "reversi.h"

using namespace std;



Square& Square::operator=(SquareValue value) {
    this->value_ = value;
    return *this;
}

bool Square::operator==(SquareValue value) const {
    return (this->value_ == value);
}

bool Square::operator!=(SquareValue value) const {
    return (this->value_ != value);
}

void Square::flip()
{
    switch (value_)
    {
    case WHITE:
        value_ = BLACK;
        break;
    case BLACK:
        value_ = WHITE;
        break;
    default:
        break;
    }
}

Square::SquareValue opposite_color(Square::SquareValue value)
{
    switch (value)
    {
    case Square::WHITE:
        return Square::BLACK;
    case Square::BLACK:
        return Square::WHITE;
    default:
        throw invalid_argument("Illegal square value");
    }
}





Board::Board(size_t s) {
    dimension_ = s;
    squares_ = new Square*[s];
    for (int i=0; i<s; i++) {
        Square* temp = new Square[s];
        for (int j=0; j<s; j++) {
            temp[j] = Square::FREE;
        }
        squares_[i] = temp;
    }
}

Board::~Board() {
    for (int i=0; i<dimension_; i++) {
        delete[] squares_[i];
    }
    delete[] squares_;
}

Board::Board(const Board &b) {
    dimension_ = b.dimension_;
    squares_ = new Square*[dimension_];
    for (int i=0; i<dimension_; i++) {
        Square* temp = new Square[dimension_];
        for (int j=0; j<dimension_; j++) {
            temp[j] = b.squares_[i][j];
        }
        squares_[i] = temp;
    }
}

Square& Board::operator()(char row, size_t column)
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1]; 
}

Square const& Board::operator()(char row, size_t column) const
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

bool Board::is_legal_and_opposite_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] != Square::FREE && squares_[row_index][column - 1] != turn;
    }
    return false;
}

bool Board::is_legal_and_same_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] == turn;
    }
    return false;
}

bool Board::is_valid_location(char row, size_t column) const
{
    size_t row_index = row_to_index(row);
    return row_index < dimension_ && column - 1 < dimension_;
}

Checkpoint::Checkpoint(const Board& b, Square::SquareValue turn) :
    board_(b),
    turn_(turn)
{

}

ostream& Board::print(ostream& out) const
{
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        if (i < 10)
        {
            out << " ";
        }
        else
        {
            out << (i / 10);
        }
    }
    out << endl;
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        out << (i % 10);
    }
    out << endl;
    for (size_t i = 0; i < dimension_; i++)
    {
        out << (char)('a' + i) << ':';
        for (size_t k = 0; k < dimension_; k++)
        {
            out << squares_[i][k];
        }
        out << endl;
    }
    return out;
}

Reversi::Reversi(size_t size) : board_(Board(size)) {
    board_(size/2 - 1 + 'a', size/2) = Square::BLACK;
    board_(size/2 + 'a', size/2) = Square::WHITE;
    board_(size/2 + 'a', size/2 + 1) = Square::BLACK;
    board_(size/2 - 1 + 'a', size/2 + 1) = Square::WHITE;
    turn_ = Square::BLACK;
}

void Reversi::play() {
    while (!is_game_over()) {
        prompt();
        char in;
        std::cin >> in;
        if (in == 'q') {
            break;
        }
        else if (in == 'c') {
            save_checkpoint();
        }
        else if (in == 'u') {
            undo();
        }
        else if (in == 'p') {
            char row;
            int col;
            std::cin >> row >> col;
            if (is_legal_choice(row, col, turn_)) {
                const size_t direction_count = 8;
                const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
                const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};
                // Now check in each directions
                for (size_t d = 0; d < direction_count; d++) {
                    // Where we're checking
                    char cursor_row = row + direction_row[d];
                    size_t cursor_column = col + direction_column[d];
                    // Move towards the direction while we're on the opposite color
                    bool found_opposite = false;
                    while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_)) {
                        found_opposite = true;
                        cursor_row += direction_row[d];
                        cursor_column += direction_column[d];
                    }
                    // Check if the next thing after is our color
                    bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);
                    // If this direction is valid, the move is valid, so short circuit and return
                    if (found_opposite && found_same) {
                        cursor_row = row + direction_row[d];
                        cursor_column = col + direction_column[d];
                        board_(row, col) = turn_;
                        while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_)) {
                            board_(cursor_row, cursor_column).flip();
                            cursor_row += direction_row[d];
                            cursor_column += direction_column[d];
                        }
                    }
                }
                turn_ = opposite_color(turn_);
            }
        }
    }

}

void Reversi::prompt() const
{
    cout << board_ << endl;
    cout << (turn_ == Square::BLACK ? "B" : "W");
    cout << " - Enter 'p r/c', 'q', 'c', 'u':" << endl;
}

void Reversi::win_loss_tie_message(size_t white_count, size_t black_count)
{
    cout << board_ << endl;
    if (white_count > black_count)
    {
        cout << "W wins" << endl;
    }
    else if (white_count < black_count)
    {
        cout << "B wins" << endl;
    }
    else
    {
        cout << "Tie" << endl;
    }
    cout << "W=" << white_count << "/B=" << black_count << endl;
}

bool Reversi::is_legal_choice(char row, size_t column, Square::SquareValue turn) const
{
    // Vectors for each cardinal direction
    const size_t direction_count = 8;
    const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
    const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};

    // Make sure location is free
    if (board_(row, column) != Square::FREE)
    {
        return false;
    }

    // Now check in each directions
    for (size_t d = 0; d < direction_count; d++)
    {
        // Where we're checking
        char cursor_row = row + direction_row[d];
        size_t cursor_column = column + direction_column[d];

        // Move towards the direction while we're on the opposite color
        bool found_opposite = false;
        while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
        {
            found_opposite = true;
            cursor_row += direction_row[d];
            cursor_column += direction_column[d];
        }

        // Check if the next thing after is our color
        bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);

        // If this direction is valid, the move is valid, so short circuit and return
        if (found_opposite && found_same) {
            return true;
        }
    }
    return false;
}

bool Reversi::is_game_over() const
{
    for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++)
    {
        for (size_t column = 1; column <= board_.dimension(); column++)
        {
            if (is_legal_choice(row, column, turn_))
            {
                return false;
            }
        }
    }
    return true;
}

void Reversi::save_checkpoint() {
    Board b(board_);
    Checkpoint cp(b, turn_);
    history_.push_back(cp);
}

void Reversi::undo() {
    if (!history_.empty()) {
        Checkpoint cp = history_.front();
        history_.pop_back();
        board_ = cp.board_;
        turn_ = cp.turn_;
    }
}

