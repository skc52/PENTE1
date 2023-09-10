#include "Tournament.h"
#include "Round.h"
#include "Player.h"
#include "ComputerStrategy.h"
#include "Board.h"
#include <iostream>

ComputerStrategy::ComputerStrategy()
{
}

// Inside the ComputerStrategy class

int ComputerStrategy::calculateConsecutivesPriority(int row, int col, Board *board, Player *computerPlayer)
{
    // Initialize priority to 0
    int priority = 0;

    // Define directions for checking consecutive pieces
    int dx[] = {1, 0, 1, 1}; // Right, Down, Diagonal Right-Down, Diagonal Right-Up
    int dy[] = {0, 1, 1, -1};

    // Iterate through each direction
    for (int direction = 0; direction < 4; ++direction)
    {
        // Check opportunities to the right and left, considering the empty space as part of the consecutive

        int ownPiecesCount = 0;
        int emptyCount = 1;
        bool emptyEdge = false;

        // considering the empty space as the rightmost piece for a consecutive
        if ((board->isWithinBounds(row + dx[direction], col + dy[direction]) && board->getPiece(row + dx[direction], col + dy[direction]) == '0') || !(board->isWithinBounds(row + dx[direction], col + dy[direction])))

        {
            // Check to the left
            for (int d = 1; d < 5; ++d)
            {
                if (!board->isWithinBounds(row - d * dx[direction], col - d * dy[direction]))
                {
                    break;
                }
                if (d < 4)
                {
                    if (board->getPiece(row - d * dx[direction], col - d * dy[direction]) == computerPlayer->getColor())
                    {
                        ownPiecesCount++;
                    }
                    else if (board->getPiece(row - d * dx[direction], col - d * dy[direction]) == '0')
                    {
                        emptyCount++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                { // check for edge empty or not..if empty and there are 3 pieces consecutive already, this is a very high priorty move
                    if (board->getPiece(row - d * dx[direction], col - d * dy[direction]) == '0')
                    {
                        emptyEdge = true;
                    }
                }
            }

            if (emptyCount + ownPiecesCount == 4)
            {
                priority = std::max(priority, ownPiecesCount);

                if (ownPiecesCount == 3)
                {
                    priority = std::max(priority, 5); // tessera formation
                }
                if (emptyEdge && ownPiecesCount == 3)
                {
                    priority = std::max(priority, 10); // tessera formation
                }
            }
        }

        ownPiecesCount = 0;
        emptyCount = 1;
        emptyEdge = false;

        // considering the empty space as the leftMost piece for a consecutive
        if ((board->isWithinBounds(row - dx[direction], col - dy[direction]) && board->getPiece(row - dx[direction], col - dy[direction]) == '0') || !(board->isWithinBounds(row - dx[direction], col - dy[direction])))
        {
            // Check to the right
            for (int d = 1; d < 5; ++d)
            {
                if (!board->isWithinBounds(row + d * dx[direction], col + d * dy[direction]))
                {
                    break;
                }
                if (d < 4)
                {
                    if (board->getPiece(row + d * dx[direction], col + d * dy[direction]) == computerPlayer->getColor())
                    {
                        ownPiecesCount++;
                    }
                    else if (board->getPiece(row + d * dx[direction], col + d * dy[direction]) == '0')
                    {
                        emptyCount++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (board->getPiece(row + d * dx[direction], col + d * dy[direction]) == '0')
                    {
                        emptyEdge = true;
                    }
                }
            }

            if (emptyCount + ownPiecesCount == 4)
            {
                priority = std::max(priority, ownPiecesCount);
                if (ownPiecesCount == 3)
                {
                    priority = std::max(priority, 5); // tessera formation
                }
                if (emptyEdge && ownPiecesCount == 3)
                {
                    priority = std::max(priority, 10); // tessera formation
                }
            }

            // Consider the empty space at position 2 of the 4 consecutive
            // It needs to have 1 empty or own piece in left directions and 2 empty or own in right
            // id there are no empty spaces, all own pieces, and the edges are open add 5 more to the priority
            ownPiecesCount = 0;
            emptyCount = 0;

            int newRow1 = row + dx[direction];
            int newCol1 = col + dy[direction];
            int newRow2 = row - dx[direction];
            int newCol2 = col - dy[direction];

            // if (board->isWithinBounds(newRow1, newCol1))
            // {
            //     if (board->getPiece(newRow1, newCol1) == computerPlayer->getColor())
            //     {
            //         ownPiecesCount++;
            //     }
            //     else if (board->getPiece(newRow1, newCol1) == '0')
            //     {
            //         emptyCount++;
            //     }
            // }
            bool edgeLeftOpen = false;
            if (board->isWithinBounds(newRow2, newCol2))
            {
                if (board->getPiece(newRow2, newCol2) == computerPlayer->getColor())
                {
                    ownPiecesCount++;
                }
                else if (board->getPiece(newRow2, newCol2) == '0')
                {
                    emptyCount++;
                }
            }

            newRow2 = row - 2 * dx[direction];
            newCol2 = col - 2 * dy[direction];

            if (board->isWithinBounds(newRow2, newCol2))
            {
                if (board->getPiece(newRow2, newCol2) == '0')
                {
                    edgeLeftOpen = true;
                }
            }

            bool edgeRightOpen = true;

            if (emptyCount + ownPiecesCount == 1)
            {
                int prevOwnPiecesCount = ownPiecesCount;
                emptyCount = 0;
                ownPiecesCount = 0;

                for (int d = 1; d < 4; ++d)
                {

                    if (!board->isWithinBounds(row + d * dx[direction], col + d * dy[direction]))
                    {
                        break;
                    }

                    if (d < 3)
                    {
                        if (board->getPiece(row + d * dx[direction], col + d * dy[direction]) == computerPlayer->getColor())
                        {
                            ownPiecesCount++;
                        }
                        else if (board->getPiece(row + d * dx[direction], col + d * dy[direction]) == '0')
                        {
                            emptyCount++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (board->getPiece(row + d * dx[direction], col + d * dy[direction]) == '0')
                        {
                            edgeRightOpen = true;
                        }
                    }
                }

                if (emptyCount + ownPiecesCount == 2)
                {
                    priority = std::max(priority, ownPiecesCount + prevOwnPiecesCount);
                    if (priority == 3)
                    {
                        priority = std::max(priority, 5); // tessera formation
                    }
                    if (edgeLeftOpen && edgeRightOpen && priority == 3)
                    {
                        priority = std::max(priority, 10); // tessera formation
                    }
                }
            }

            // Consider the empty space at position 3 of the 4 consecutive
            // It needs to have 2 empty or own pieces in left direction and 1 empty or own piece in the right direction
            ownPiecesCount = 0;
            emptyCount = 0;
            edgeLeftOpen = false;
            edgeRightOpen = false;
            if (board->isWithinBounds(row + dx[direction], col + dy[direction]))
            {
                if (board->getPiece(row + dx[direction], col + dy[direction]) == computerPlayer->getColor())
                {
                    ownPiecesCount++;
                }
                else if (board->getPiece(row + dx[direction], col + dy[direction]) == '0')
                {
                    emptyCount++;
                }
            }
            if (board->isWithinBounds(row + 2 * dx[direction], col + 2 * dy[direction]))
            {
                if (board->getPiece(row + 2 * dx[direction], col + 2 * dy[direction]) == '0')
                {
                    edgeRightOpen = true;
                }
            }

            if (emptyCount + ownPiecesCount == 1)
            {
                int prevOwnPiecesCount = ownPiecesCount;
                emptyCount = 0;
                ownPiecesCount = 0;

                for (int d = 1; d < 4; ++d)
                {

                    if (!board->isWithinBounds(row - d * dx[direction], col - d * dy[direction]))
                    {
                        break;
                    }

                    if (d < 3)
                    {
                        if (board->getPiece(row - d * dx[direction], col - d * dy[direction]) == computerPlayer->getColor())
                        {
                            ownPiecesCount++;
                        }
                        else if (board->getPiece(row - d * dx[direction], col - d * dy[direction]) == '0')
                        {
                            emptyCount++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (board->getPiece(row - d * dx[direction], col - d * dy[direction]) == '0')
                        {
                            edgeLeftOpen = true;
                        }
                    }
                }

                if (emptyCount + ownPiecesCount == 2)
                {
                    priority = std::max(priority, ownPiecesCount + prevOwnPiecesCount);
                    if (priority == 3)
                    {
                        priority = std::max(priority, 5);
                    }
                    if (edgeLeftOpen && edgeRightOpen && priority == 3)
                    {
                        priority = std::max(priority, 10); // tessera formation
                    }
                }
            }
        }
    }

    return priority;
}

int ComputerStrategy::calculateCapturePairsPriority(int row, int col, Board *board, Player *computerPlayer, Round *r)
{
    // Implement logic to check if it captures pairs or creates a chance for capturing pairs.
    // Assign a priority value accordingly. Return the calculated priority.
    int priority = 0;
    // Your implementation here
    // Define directions for checking consecutive pieces
    int dx[] = {1, 0, 1, 1}; // Right, Down, Diagonal Right-Down, Diagonal Right-Up
    int dy[] = {0, 1, 1, -1};

    // Iterate through each direction
    char enemyPiece = computerPlayer->getColor() == 'W' ? 'B' : 'W';
    for (int direction = 0; direction < 4; ++direction)
    {
        // check left
        // if capture is sure
        if (board->isWithinBounds(row - dx[direction], col - dy[direction]) && board->getPiece(row - dx[direction], col - dy[direction]) == enemyPiece && board->isWithinBounds(row - dx[direction] * 2, col - dy[direction] * 2) && board->getPiece(row - dx[direction] * 2, col - dy[direction] * 2) == enemyPiece)
        {
            // sure capture
            if (board->isWithinBounds(row - dx[direction] * 3, col - dy[direction] * 3) && board->getPiece(row - dx[direction] * 3, col - dy[direction] * 3) == computerPlayer->getColor())
            {
                priority = std::max(priority, 5);

                if (r->getPairsCapturedNum(computerPlayer) == 4)
                {
                    priority = std::max(priority, 10);
                }
            }
            else
            {
                priority = std::max(priority, 2);
            }
        }

        // if set up for capture

        // check right

        if (board->isWithinBounds(row + dx[direction], col + dy[direction]) && board->getPiece(row + dx[direction], col + dy[direction]) == enemyPiece && board->isWithinBounds(row + dx[direction] * 2, col + dy[direction] * 2) && board->getPiece(row + dx[direction] * 2, col + dy[direction] * 2) == enemyPiece)
        {
            // sure capture
            if (board->isWithinBounds(row + dx[direction] * 3, col + dy[direction] * 3) && board->getPiece(row + dx[direction] * 3, col + dy[direction] * 3) == computerPlayer->getColor())
            {
                priority = std::max(priority, 5);

                if (r->getPairsCapturedNum(computerPlayer) == 4)
                {
                    priority = std::max(priority, 10);
                }
            }
            else
            {
                priority = std::max(priority, 2);
            }
        }
    }
    return priority;
}

int ComputerStrategy::calculateEndGamePriorityWith5Consectuives(int row, int col, Board *board, Player *computerPlayer)
{
    // Implement logic to check if it can end the game with 5 consecutives.
    // Assign a priority value accordingly. Return the calculated priority.
    int priority = 0;
    // Your implementation here
    // Define directions for checking capture pairs
    int dx[] = {1, 0, 1, 1}; // Right, Down, Diagonal Right-Down, Diagonal Right-Up
    int dy[] = {0, 1, 1, -1};

    // Iterate through each direction
    for (int direction = 0; direction < 4; ++direction)
    {
        // check to see if in the current direction, placing own piece in the empty space will create a 5 consecutive
        // get the number of consecutives in the left and the number of consecutives in the righ
        // if the sum >= 4, game winning chance
        // add 3 to the priority
        bool isConsecutive = true;
        int leftCount = 0;
        int rightCount = 0;
        while (isConsecutive)
        {
            int newRow = row - dx[direction] * (leftCount + 1);
            int newCol = col - dy[direction] * (leftCount + 1);
            if (board->getPiece(newRow, newCol) == computerPlayer->getColor())
            {
                leftCount++;
            }
            else
            {
                isConsecutive = false;
            }
        }
        isConsecutive = true;
        while (isConsecutive)
        {
            int newRow = row + dx[direction] * (rightCount + 1);
            int newCol = col + dy[direction] * (rightCount + 1);
            if (board->getPiece(newRow, newCol) == computerPlayer->getColor())
            {
                rightCount++;
            }
            else
            {
                isConsecutive = false;
            }
        }

        if (leftCount + rightCount >= 4)
        {
            priority = std::max(priority, 10); // game point
        }
    }

    return priority;
}

int ComputerStrategy::calculateStopOpponentPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer)
{
    // Implement logic to check if it stops or ruins the opponent's chances of getting 4 or 5 consecutives.
    // Assign a priority value accordingly. Return the calculated priority.

    // Your implementation here

    // determine the priority for human player
    // put the computer piece in that max priority position
    return calculateConsecutivesPriority(row, col, board, humanPlayer);
}

int ComputerStrategy::calculateStopRuiningPriority(int row, int col, Board *board, Player *computerPlayer)
{
    // Implement logic to check if it stops the opponent from ruining the game.
    // Assign a priority value accordingly. Return the calculated priority.
    int priority = 0;
    // Your implementation here
    return priority;
}

int ComputerStrategy::calculateCaptureRiskPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer, Round *r)
{
    // Implement logic to check if the computer player gets captured or potentially captured in the future with this move.
    // Assign a priority value accordingly. Return the calculated priority.
    int priority = 0;
    // Your implementation here
    return calculateCapturePairsPriority(row, col, board, humanPlayer, r);
}

int ComputerStrategy::calculateCenterProximityPriority(int row, int col, Board *board)
{
    // Implement logic to consider how close to the center of the board the move is.
    // Assign a priority value accordingly. Return the calculated priority.
    int priority = 0;

    // Your implementation here

    return priority;
}

std::string ComputerStrategy::convertPosToString(int row, int col)
{

    // col t0 Alphabet equivalent
    // col starts from 1 to 19
    char colAlphabet = 'A' + col - 1;
    std::string rowString = std::to_string(20 - row); // because row label is inverted
    std::string inputString = colAlphabet + rowString;
    std::cout << "Computer placed at " << inputString << std::endl;
    return inputString;
}

std::string ComputerStrategy::determineBestPosition(Board *board, Player *computerPlayer, Player *humanPlayer, Round *r)
{
    int maxPriority = -1;
    int bestRow = -1, bestCol = -1;
    int boardSize = 20;
    int boardPriority[20][20] = {0};
    for (int row = 1; row < boardSize; row++)
    {
        for (int col = 1; col < boardSize; col++)
        {
            std::cout << board->getPiece(1, 1) << std::endl;
            if (board->getPiece(row, col) == '0')
            {
                int priority = std::max(-1, calculateConsecutivesPriority(row, col, board, computerPlayer));
                priority = std::max(priority, calculateCapturePairsPriority(row, col, board, computerPlayer, r));
                priority = std::max(priority, calculateEndGamePriorityWith5Consectuives(row, col, board, computerPlayer));
                priority = std::max(priority, 2 * calculateStopOpponentPriority(row, col, board, computerPlayer, humanPlayer));
                // priority += calculatestopruiningpriority(row, col, board, computerplayer);
                priority = std::max(priority, 2 * calculateCaptureRiskPriority(row, col, board, computerPlayer, humanPlayer, r));
                // priority += calculatecenterproximitypriority(row, col, board);

                if (priority > maxPriority)
                {
                    maxPriority = priority;
                    bestRow = row;
                    bestCol = col;
                }
                boardPriority[row][col] = priority;
                // std::cout << "Row and col " << row << " " << col << " priority " << priority << std::endl;
            }
        }
    }
    for (int row = 1; row < boardSize; row++)
    {
        for (int col = 1; col < boardSize; col++)
        {
            std::cout << boardPriority[row][col] << " ";
        }
        std::cout << std::endl;
    }
    // board->DisplayBoard(r);

    // Place the computer player's piece at (bestRow, bestCol)
    std::cout << " In computerstrategycpp, bestrow and best col" << bestRow << " " << bestCol << std::endl;
    return convertPosToString(bestRow, bestCol);
}
