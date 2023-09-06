#include "Board.h"
#include "Player.h"
#include "Round.h"
#include <iostream>

// Constructor
Board::Board()
{

    resetBoard();
}

// Member function to reset the board
void Board::resetBoard()
{
    std::cout << "Initializing the board\n";

    // add col labels
    for (int i = 1; i < 20; i++)
    {
        board[0][i] = 'A' + i - 1;
    }

    char columnLabel[20] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // add row labels
    for (int i = 19; i >= 1; i--)
    {
        board[i][0] = static_cast<char>(19 - i + 1 + 48);
    }

    // reset the pieces..set every intersection to empty
    for (int i = 1; i < 20; i++)
    {
        for (int j = 1; j < 20; j++)
        {
            board[i][j] = '0';
        }
    }
}

// Member function to place the player's piece in the desired intersection
bool Board::placeYourPiece(Round *r) // will return false if the game has ended
{                                    // TODO this should be in Player class
    // Implement this method to handle player input and game logic
    // keep on asking until a valid input is given
    //   askInput();

    // place the piece, if it is the first turn place in the centre
    if (r->getTurnNum() == 0 && r->getCurrentPlayer()->getColor() == 'W')
    {
        board[10][10] = 'W';
    }
    else
    {
        board[this->row][this->col] = r->getCurrentPlayer()->getColor();

        // if valid, check for pairs to capture
        if (checkAndCapture(r, r->getCurrentPlayer(), r->getNextPlayer()))
        {
            // count the fours and update in  round
            checkForFours(r, r->getCurrentPlayer()->getColor());
            std::cout << r->getCurrentPlayer()->getName() << " won the game\n";
            return false;
        }
        // also checks for 5 consecutive pieces, if so game terminates
        // TODO: how to terminate the game
        if (checkForFive(r))
        { // if five consecutive return false to end the game loop
            checkForFours(r, r->getCurrentPlayer()->getColor());
            std::cout << r->getCurrentPlayer()->getName() << " won the game\n";
            return false;
        }
    }
    return true;
    // if game is still continuining, pass the turn
    // changeTurn();
}

// Member function to check the validity of the inputted position
bool Board::checkValidity()
{
    // Implement this method to check if the position is valid
    // private members row and col hold the inputted values
    // position must be within bounds and empty

    // TODO FOR THE SECOND TURN OF WHITE, MUST BE PLACED 3 steps away from the center
    if (isWithinBounds(this->row, this->col) && board[row][col] == '0')
    {
        return true;
    }
    if (isWithinBounds(this->row, this->col))
    {
        showComment("Out of Bounds");
        return false;
    }

    showComment("Position not empty!");
    return false;
}

// Member function to check and capture pairs of pieces
bool Board::checkAndCapture(Round *r, Player *p, Player *e) // returns true if game has ended
{
    // Implement this method to check for pairs and capture them
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    // Check for pairs in each direction
    for (int i = 0; i < 4; i++)
    {
        int dx = directions[i][0]; // x-direction
        int dy = directions[i][1]; // y-direction

        // Check for pairs in the forward direction
        if (checkForPairs(p, e, dx, dy))
        {
            // Capture pairs in the forward direction
            if (capturePairs(r, p, dx, dy))
            {
                return true;
            }
        }

        // Check for pairs in the backward direction
        if (checkForPairs(p, e, -dx, -dy))
        {
            // Capture pairs in the backward direction
            if (capturePairs(r, p, -dx, -dy))
            {
                return true;
            }
        }
    }

    return false;
}

// Member function to check for pairs in a specific direction
bool Board::checkForPairs(Player *p, Player *e, int dx, int dy) // p is the player, e is the enemy
{
    // Implement this method to check for pairs in the given direction
    char currentPlayerPiece = board[this->row][this->col]; // Current player's piece

    // Calculate the positions of the next two pieces in the specified direction
    int nextRow1 = this->row + dx;
    int nextCol1 = this->col + dy;
    int nextRow2 = this->row + 2 * dx;
    int nextCol2 = this->col + 2 * dy;
    int nextRow3 = this->row + 3 * dx;
    int nextCol3 = this->col + 3 * dy;

    // Check if the next two positions and the piece after that are within the board bounds
    if (!isWithinBounds(nextRow1, nextCol1) || !isWithinBounds(nextRow2, nextCol2) || !isWithinBounds(nextRow3, nextCol3))
    {
        return false;
    }

    // Check if the next two pieces are enemies and the piece after that is the player's own
    if (board[nextRow1][nextCol1] == e->getColor() &&
        board[nextRow2][nextCol2] == e->getColor() &&
        board[nextRow3][nextCol3] == p->getColor())
    {
        return true; // Pairs are capturable
    }

    return false; // Pairs are not capturable
}

// Member function to capture pairs of pieces
bool Board::capturePairs(Round *r, Player *p, int dx, int dy) // returns true if game has ended with 5 captures
{
    // Implement this method to check for pairs in the given direction
    char currentPlayerPiece = board[this->row][this->col]; // Current player's piece

    // Calculate the positions of the next two pieces in the specified direction
    int nextRow1 = this->row + dx;
    int nextCol1 = this->col + dy;
    int nextRow2 = this->row + 2 * dx;
    int nextCol2 = this->col + 2 * dy;

    // Set the captured pieces to 0 (empty)
    board[nextRow1][nextCol1] = '0';
    board[nextRow2][nextCol2] = '0';

    // TODO update scores for players
    r->setPairsCapturedNum(p);
    //  TODO captured pair == 5, game won, announce winner, closing stats, checkforfours
    if (r->getPairsCapturedNum(p) == 5)
    {
        r->setGamePoints(p);
        r->announceWinnerOfTheRound(p);
        return true;
    }

    return false;
}

// Member function to check for five consecutive pieces
bool Board::checkForFive(Round *r)
{
    // Implement this method to check for five consecutive pieces
    char currentPlayerPiece = board[this->row][this->col]; // Current player's piece

    // Define directions: horizontal, vertical, and both diagonals
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    // Check for five consecutive pieces in each direction
    for (int i = 0; i < 4; i++)
    {
        int dx = directions[i][0]; // x-direction
        int dy = directions[i][1]; // y-direction

        // Initialize the count to 1 (counting the current piece)
        int count = 1;

        // Check in the positive direction
        int x = row + dx;
        int y = col + dy;
        while (isWithinBounds(x, y) && board[x][y] == currentPlayerPiece)
        {
            count++;
            x += dx;
            y += dy;
        }

        // Check in the negative direction
        x = row - dx;
        y = col - dy;
        while (isWithinBounds(x, y) && board[x][y] == currentPlayerPiece)
        {
            count++;
            x -= dx;
            y -= dy;
        }

        // TODO:If there are five or more consecutive pieces, add 5 points and stop the game loop
        // the winner of this round
        // will start the next round, if the game continues
        if (count >= 5)
        {
            r->setGamePoints(r->getCurrentPlayer());
            r->announceWinnerOfTheRound(r->getCurrentPlayer());
            return true;
        }
    }
    return false; // No five consecutive pieces found
}

// Member function to count the number of consecutive 4s throughout the board
int Board::checkForFours(Round *r, char piece)
{
    // Implement this method to count consecutive 4 pieces
    int foursCount = 0;

    // Define directions: horizontal, vertical, and both diagonals
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    // start at the beginning of each row and calculate the number of consecutive 4s
    for (int i = 1; i < 20; i++)
    {
        for (int j = 1; j < 16; j++)
        { // 16 to prevent out of bounds, for columns more than 16 there wont be consecutive 4s starting at that point
            bool consecutive4 = true;
            for (int k = 0; k < 4; k++)
            {
                if (board[i][j + k] != piece)
                {
                    consecutive4 = false;
                    j += k;
                    break;
                }
            }
            if (consecutive4)
            {
                foursCount++;
            }
        }
    }

    // start at the beginning of each column and calculate the number of consecutive 4s
    for (int i = 1; i < 20; i++)
    {
        for (int j = 1; j < 16; j++)
        { // 16 to prevent out of bounds, for columns more than 16 there wont be consecutive 4s starting at that point
            bool consecutive4 = true;
            for (int k = 0; k < 4; k++)
            {
                if (board[j + k][i] != piece)
                {
                    consecutive4 = false;
                    j += k;
                    break;
                }
            }
            if (consecutive4)
            {
                foursCount++;
            }
        }
    }

    // iterate through forward diagonals formula:row+k, col+k
    // starting column as 1 for each diagonal, start from row 16, and move your way up to row 1,
    // start from 16 since there wont be consecutive4s starting after 16
    for (int i = 16; i >= 1; i--)
    { // row
        for (int j = 1; j < 20 - i + 1; j++)
        { // col
            bool consecutive4 = true;
            for (int k = 0; k < 4; k++)
            {
                if (board[i + k][j + k] != piece)
                {
                    consecutive4 = false;
                    j += k;
                    break;
                }
            }
            if (consecutive4)
            {
                foursCount++;
            }
        }
    }
    // starting row as 1 for each diagonal, start from col2 since col1 is already covered above , and move right until col 16;
    // upto 16 since there wont be consecutive4s starting after 16
    for (int i = 2; i < 17; i++)
    { // col
        for (int j = 1; j < 20 - i + 1; j++)
        { // row
            bool consecutive4 = true;
            for (int k = 0; k < 4; k++)
            {
                if (board[j + k][i + k] != piece)
                {
                    consecutive4 = false;
                    j += k;
                    break;
                }
            }
            if (consecutive4)
            {
                foursCount++;
            }
        }
    }

    // iterate through backward diagonals formula:row-k, col+k

    // iterate through the backward diagnols, starting from the bottom row upto row4
    for (int i = 19; i >= 4; i--)
    { // row
        for (int j = 1; j <= i; j++)
        { // col
            bool consecutive4 = true;
            for (int k = 0; k < 4; k++)
            {
                if (board[i - k][j + k] != piece)
                {
                    consecutive4 = false;
                    j += k;
                    break;
                }
            }
            if (consecutive4)
            {
                foursCount++;
            }
        }
    }

    // iterate through the backward diagnols, starting from the col 2 upto col 16
    for (int i = 2; i < 17; i++)
    { // col
        for (int j = 2; j < 20 - i + 1; j++)
        { // row
            bool consecutive4 = true;
            for (int k = 0; k < 4; k++)
            {
                if (board[j - k][i + k] != piece)
                {
                    consecutive4 = false;
                    j += k;
                    break;
                }
            }
            if (consecutive4)
            {
                foursCount++;
            }
        }
    }

    r->setFourConsecutive(r->getCurrentPlayer(), foursCount);

    return foursCount;
}

// Member function to display the board
void Board::DisplayBoard(Round *r)
{
    std::cout << "Displaying the board\n";

    // Implement this method to display the game board, scores, and turn
    for (int i = 0; i < 20; i++)
    {

        std::cout << 20 - i << " ";
        if (20 - i <= 9)
        {
            std::cout << " ";
        }
        for (int j = 1; j < 20; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // Do not show 4consecutives here. we will show at the end
    std::cout << r->getCurrentPlayer()->getName() << "'s turn. Color is " << r->getCurrentPlayer()->getColor() << std::endl;
    std::cout << "Pairs captured = " << r->getPairsCapturedNum(r->getCurrentPlayer()) << std::endl;

    std::cout << r->getNextPlayer()->getName() << "'s turn. Color is " << r->getNextPlayer()->getColor() << std::endl;
    std::cout << "Pairs captured = " << r->getPairsCapturedNum(r->getNextPlayer()) << std::endl;
}

// Member function to parse input into board indices
bool Board::parsePosition(const std::string &input)
{
    // Implement this method to parse the input into row and column indices
    if ((input.size() == 1 && tolower(input[0]) != 'h') && input.size() > 3)
    {
        showComment("Invalid Input");
        return false;
    }

    // TODO
    if (input.size() == 1 && tolower(input[0]) == 'h')
    {
        // provide help
        // this help will come from Strategy class and that has not been implemented yet
        // once it shows the suggested intersection, reprompt the human player to put in his input
        // to do that return false, because if parsePosition returns false, the while loop continues
        // skipping the checkValidity step
        return false;
    }

    // input = toupper(input);
    char colChar = toupper(input[0]);
    int numericEquivalent = colChar - 'A' + 1;
    std::cout << "Column " << numericEquivalent << "was entered\n";
    if (numericEquivalent < 1 || numericEquivalent > 19)
    {
        showComment("Enter column from A - S only");
        return false;
    }
    this->col = numericEquivalent;

    std::string rowString = input.substr(1);
    try
    {
        this->row = 20 - std::stoi(rowString);
    }
    catch (const std::invalid_argument &e)
    {
        showComment("Invalid row position. Enter row between 1 to 19");
        return false;
    }

    if (this->row < 1 || this->row > 19)
    {
        showComment("Invalid row position. Enter row between 1 to 19");
        return false;
    }

    return true;
}

// Member function to show comments for invalid moves
void Board::showComment(const std::string &comment)
{
    std::cout << "Error: " << comment << std::endl;
}

// Private helper function to check if a position is valid
bool Board::isWithinBounds(int row, int col)
{
    // Implement this method to check if the position is within bounds
    return row >= 1 && row <= 19 && col >= 1 && col <= 19;
}
