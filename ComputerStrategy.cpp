#include "Tournament.h"
#include "Round.h"
#include "Player.h"
#include "ComputerStrategy.h"
#include "Board.h"
#include <iostream>

ComputerStrategy::ComputerStrategy(Tournament *t)
{
    this->t = t;
}

int ComputerStrategy::calculateConsecutivesPriority(int row, int col, Board *board, Player *computerPlayer)
{
    int priority = 0;

    // Define directions for checking consecutive pieces
    int dx[] = {1, 0, 1, 1}; // Right, Down, Backward Diagonal, Forward Diagonal
    int dy[] = {0, 1, 1, -1};

    // Iterate through each direction
    for (int direction = 0; direction < 4; ++direction)
    {
        // Check opportunities to the right and left, considering the empty space as part of the consecutive

        int ownPiecesCount = 0;
        int emptyCount = 1;     // because we are considering the empty space as the rightmost piece
        bool emptyEdge = false; // if the edge is empty then it might lead to a tessera formation

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
                priority = std::max(priority, 2 * ownPiecesCount); // at most 4

                if (ownPiecesCount == 3)
                {
                    priority = std::max(priority, 10);
                }

                // highest priority move,,,because not only you can get a 4 consecutives but also 5 consecutives is sure
                if (emptyEdge && ownPiecesCount == 3)
                {
                    priority = std::max(priority, 15); // tessera formation
                }
            }
        }

        // now do the same for right side
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
                priority = std::max(priority, 2 * ownPiecesCount); // at most 4
                if (ownPiecesCount == 3)
                {
                    priority = std::max(priority, 10);
                }
                if (emptyEdge && ownPiecesCount == 3)
                {
                    priority = std::max(priority, 15); // tessera formation
                }
            }
        }
        // Consider the empty space at position 2 of the 4 consecutive
        // It needs to have 1 empty or own piece in left directions and 2 empty or own in right
        // id there are no empty spaces, all own pieces, and the edges are open add 5 more to the priority
        ownPiecesCount = 0;
        emptyCount = 0;
        bool edgeLeftOpen = false;
        bool edgeRightOpen = false;

        if (board->isWithinBounds(row - dx[direction], col - dy[direction]))
        {
            if (board->getPiece(row - dx[direction], col - dy[direction]) == computerPlayer->getColor())
            {
                ownPiecesCount++;
            }
            else if (board->getPiece(row - dx[direction], col - dy[direction]) == '0')
            {
                emptyCount++;
            }
        }
        if (board->isWithinBounds(row - 2 * dx[direction], col - 2 * dy[direction]))
        {
            if (board->getPiece(row - 2 * dx[direction], col - 2 * dy[direction]) == '0')
            {
                edgeLeftOpen = true;
            }
        }
        // at this point we determined whether we have empty space or ownpiece in the left side, and also whether the edge is empty for tessera formation
        // we do not proceed to determine priority if there is an enemy piece in the left side
        if (emptyCount + ownPiecesCount == 1)
        {
            if (ownPiecesCount == 1)
            {
                std::cout << "ONW PIECE COUNT\n";
            }
            int prevOwnPiecesCount = ownPiecesCount; // that is the no of pieces from the left side, at most its gonna be 1. either own piece, enemy piece, or empty
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

                int totalPiecesCount = ownPiecesCount + prevOwnPiecesCount;
                priority = std::max(priority, 2 * totalPiecesCount); // at most 4
                if (totalPiecesCount == 3)
                {
                    priority = std::max(priority, 10);
                }
                if (edgeLeftOpen && edgeRightOpen && totalPiecesCount == 3)
                {
                    std::cout << "Tessera formation" << std::endl;
                    priority = std::max(priority, 15); // tessera formation
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
        // at this point we determined whether we have empty space or ownpiece in the right side, and also whether the edge is empty for tessera formation
        // we do not proceed to determine priority if there is an enemy piece in the right side
        if (emptyCount + ownPiecesCount == 1)
        {
            int prevOwnPiecesCount = ownPiecesCount; // that is the no of pieces from the right side, at most its gonna be 1. either own piece, enemy piece, or empty
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
                int totalPiecesCount = ownPiecesCount + prevOwnPiecesCount;
                priority = std::max(priority, 2 * totalPiecesCount); // at most 4

                if (totalPiecesCount == 3)
                {
                    priority = std::max(priority, 10);
                }
                if (edgeLeftOpen && edgeRightOpen && totalPiecesCount == 3)
                {
                    priority = std::max(priority, 15); // tessera formation
                }
            }
        }
    }

    return priority;
}

// For sure capture pairs should have same priority as 4 for sure consecutive
//  if the capture count is 4 then the priority should be the same as 5 for sure consecutive
int ComputerStrategy::calculateCapturePairsPriority(int row, int col, Board *board, Player *computerPlayer, Round *r)
{
    // Implement logic to check if it captures pairs or creates a chance for capturing pairs.
    // Assign a priority value accordingly. Return the calculated priority.
    int priority = 0;
    // Define directions for checking consecutive pieces
    int dx[] = {1, 0, 1, 1}; // Right, Down,Backward Diagonal, Forward DIagonal
    int dy[] = {0, 1, 1, -1};

    // Iterate through each direction
    char enemyPiece = computerPlayer->getColor() == 'W' ? 'B' : 'W';
    for (int direction = 0; direction < 4; ++direction)
    {
        // check left from the empty space

        if (board->isWithinBounds(row - dx[direction], col - dy[direction]) && board->getPiece(row - dx[direction], col - dy[direction]) == enemyPiece && board->isWithinBounds(row - dx[direction] * 2, col - dy[direction] * 2) && board->getPiece(row - dx[direction] * 2, col - dy[direction] * 2) == enemyPiece)
        {
            // sure capture
            if (board->isWithinBounds(row - dx[direction] * 3, col - dy[direction] * 3) && board->getPiece(row - dx[direction] * 3, col - dy[direction] * 3) == computerPlayer->getColor())
            {

                if (r->getPairsCapturedNum(computerPlayer) < 4)
                {
                    priority = std::max(priority, 10);
                }
                else
                {
                    Player *opponent = r->getCurrentPlayer() == computerPlayer ? r->getNextPlayer() : computerPlayer;
                    int opponentScore = t->getTotalScores(opponent);
                    int ownScore = t->getTotalScores(computerPlayer);
                    if ((opponentScore - ownScore) > 0) // if opponent is winning by more than 1 points then we do not want to end the game just yet by capturing
                                                        // because we wont be able to win with that
                    {
                        priority = std::max(priority, 1);
                    }
                    else
                    {
                        if ((ownScore - opponentScore) > 3)
                        {
                            priority = std::max(priority, 8);
                        }
                        else
                        {
                            priority = std::max(priority, 6);
                        }
                    }
                }
            }
            // chances of capture
            else
            {
                // no capture
                if (!board->isWithinBounds(row - dx[direction] * 3, col - dy[direction] * 3))
                {
                    priority = std::max(priority, 4); // if cannot capture, then have to stop its chance of consecutive
                    // and for that the priority is 4 because in case of consecutives of ownpiece, if there is no immediate 4 for sure consecutive
                    // then the max priority to put own piece in that empty place is set to 4
                }
                // probably capture
                else
                {
                    priority = std::max(priority, 6); // there is a chance that it may get captured and that should be higher priority then no capture
                    // that may lead to 4 consecutives in future
                }
            }
        }

        // check right

        if (board->isWithinBounds(row + dx[direction], col + dy[direction]) && board->getPiece(row + dx[direction], col + dy[direction]) == enemyPiece && board->isWithinBounds(row + dx[direction] * 2, col + dy[direction] * 2) && board->getPiece(row + dx[direction] * 2, col + dy[direction] * 2) == enemyPiece)
        {
            // sure capture
            if (board->isWithinBounds(row + dx[direction] * 3, col + dy[direction] * 3) && board->getPiece(row + dx[direction] * 3, col + dy[direction] * 3) == computerPlayer->getColor())
            {

                if (r->getPairsCapturedNum(computerPlayer) < 4)
                {
                    priority = std::max(priority, 10);
                }

                if (r->getPairsCapturedNum(computerPlayer) == 4)
                {

                    Player *opponent = r->getCurrentPlayer() == computerPlayer ? r->getNextPlayer() : computerPlayer;
                    int opponentScore = t->getTotalScores(opponent);
                    int ownScore = t->getTotalScores(computerPlayer);
                    if ((opponentScore - ownScore) > 0) // if opponent is winning by more than 1 points then we do not want to end the game just yet by capturing
                                                        // because we wont be able to win with that
                    {
                        priority = std::max(priority, 1);
                    }
                    else
                    {
                        if ((ownScore - opponentScore) > 3)
                        {
                            priority = std::max(priority, 8);
                        }
                        else
                        {
                            priority = std::max(priority, 6);
                        }
                    }
                }
            }
            else
            {
                if (!board->isWithinBounds(row + dx[direction] * 3, col + dy[direction] * 3))
                {
                    priority = std::max(priority, 4); // if cannot capture, then have to stop its chance of consecutive
                                                      // and for that the priority is 4 because in case of consecutives of ownpiece, if there is no immediate 4 for sure consecutive
                                                      // then the max priority to put own piece in that empty place is set to 4
                }
                else
                {
                    priority = std::max(priority, 6); // there is a chance that it may get captured and that should be higher priority then no capture
                    // that may lead to 4 consecutives in future;
                }
            }
        }
    }
    return priority;
}

int ComputerStrategy::calculateEndGamePriorityWith5Consectuives(int row, int col, Board *board, Player *computerPlayer, Round *r)
{

    int priority = 0;
    // Define directions for checking capture pairs
    int dx[] = {1, 0, 1, 1}; // Right, Down,Backward Diagonal, Forward DIagonal
    int dy[] = {0, 1, 1, -1};

    // Iterate through each direction
    for (int direction = 0; direction < 4; ++direction)
    {
        // check to see if in the current direction, placing own piece in the empty space will create a 5 consecutive
        // get the number of consecutives in the left and the number of consecutives in the right
        // if the sum >= 4, game end for sure

        bool isConsecutive = true;
        int leftCount = 0;
        int rightCount = 0;
        // determine consecutive count in left side
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
        // determine consecutive count in right side
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
            // if opponent score is significantly higher and if you have a chance to get 5 consecutive for sure, then take it
            // it does not make sense to wait for getting more points as at any point enemy can end the game and even further the score gap
            Player *opponent = r->getCurrentPlayer() == computerPlayer ? r->getNextPlayer() : computerPlayer;
            int opponentScore = t->getTotalScores(opponent);
            int ownScore = t->getTotalScores(computerPlayer);

            if ((opponentScore - ownScore) > 3)
            {
                priority = std::max(priority, 15);
            }

            // case when you are winning
            // you may wanna delay and try to get more points
            else
            {
                priority = std::max(priority, 8);
            }
        }
    }

    return priority;
}

int ComputerStrategy::calculateOpponentsEndGamePriorityWith5Consectuives(int row, int col, Board *board, Player *opponentPlayer, Round *r)
{
    return calculateEndGamePriorityWith5Consectuives(row, col, board, opponentPlayer, r);
}

int ComputerStrategy::calculateStopOpponentPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer)
{
    // determine the priority for human player
    // put the computer piece in that max priority position

    return calculateConsecutivesPriority(row, col, board, humanPlayer);
}

int ComputerStrategy::calculateCaptureRiskPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer, Round *r)
{

    return calculateCapturePairsPriority(row, col, board, humanPlayer, r);
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
            if (board->getPiece(row, col) == '0')
            {
                int priority = std::max(-1, calculateConsecutivesPriority(row, col, board, r->getCurrentPlayer()));
                priority = std::max(priority, calculateCapturePairsPriority(row, col, board, r->getCurrentPlayer(), r));
                priority = std::max(priority, calculateEndGamePriorityWith5Consectuives(row, col, board, r->getCurrentPlayer(), r));
                priority = std::max(priority, 2 * calculateOpponentsEndGamePriorityWith5Consectuives(row, col, board, r->getNextPlayer(), r));
                priority = std::max(priority, calculateStopOpponentPriority(row, col, board, r->getCurrentPlayer(), r->getNextPlayer()));
                // priority += calculatestopruiningpriority(row, col, board, computerplayer);
                priority = std::max(priority, calculateCaptureRiskPriority(row, col, board, r->getCurrentPlayer(), r->getNextPlayer(), r));
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
