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

std::pair<int, std::string> ComputerStrategy::calculateConsecutivesPriority(int row, int col, Board *board, Player *computerPlayer)
{
    std::pair<int, std::string> priorityPair; // TODO
    int priority = 0;
    std::string reason = "Create chances of consecutives ";
    std::string tailToReason; // will store the direction for the reason
    // Define directions for checking consecutive pieces
    int dx[] = {1, 0, 1, 1}; // Right, Down, Backward Diagonal, Forward Diagonal
    int dy[] = {0, 1, 1, -1};
    std::string dirName[] = {"Col", "Row", "Backward Diagonal", "Forward Diagonal"};

    // Iterate through each direction
    for (int direction = 0; direction < 4; ++direction)
    {
        // Check opportunities to the right and left, considering the empty space as part of the consecutive

        int ownPiecesCount = 0;
        int emptyCount = 1; // because we are considering the empty space as the rightmost piece

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
            }

            // looking for a chance of consecutive...not necessarily for consecutives
            if (emptyCount + ownPiecesCount == 4 && ownPiecesCount != 3)
            {
                priority = std::max(priority, ownPiecesCount); // at most 2
                reason = dirName[direction];
            }
        }

        // now do the same for right side
        ownPiecesCount = 0;
        emptyCount = 1;

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
            }

            if (emptyCount + ownPiecesCount == 4 && ownPiecesCount != 3)
            {
                priority = std::max(priority, ownPiecesCount);
                reason = dirName[direction];
            }
        }
        // Consider the empty space at position 2 of the 4 consecutive
        // It needs to have 1 empty or own piece in left directions and 2 empty or own in right
        ownPiecesCount = 0;
        emptyCount = 0;

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

        // at this point we determined whether we have empty space or ownpiece in the left side
        // we do not proceed to determine priority if there is an enemy piece in the left side
        if (emptyCount + ownPiecesCount == 1)
        {
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
            }
            // looking for a chance of consecutives, not necessarily consecutives
            if (emptyCount + ownPiecesCount == 1)
            {

                int totalPiecesCount = ownPiecesCount + prevOwnPiecesCount;
                priority = std::max(priority, totalPiecesCount); // at most 2
                reason = dirName[direction];
            }
        }

        // Consider the empty space at position 3 of the 4 consecutive
        // It needs to have 2 empty or own pieces in left direction and 1 empty or own piece in the right direction
        ownPiecesCount = 0;
        emptyCount = 0;
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

        // at this point we determined whether we have empty space or ownpiece in the right side
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
            }

            if (emptyCount + ownPiecesCount == 1)
            {
                int totalPiecesCount = ownPiecesCount + prevOwnPiecesCount;
                priority = std::max(priority, totalPiecesCount); // at most 2
                reason = dirName[direction];
            }
        }
    }

    return {priority, reason};
}

// For sure capture pairs should have same priority as 4 for sure consecutive
//  if the capture count is 4 then the priority should be the same as 5 for sure consecutive
std::pair<int, std::string> ComputerStrategy::calculateCapturePairsPriority(int row, int col, Board *board, Player *computerPlayer, Round *r, bool checkingOwn)
{

    int priority = 0;
    std::string reason = "";
    // Define directions for checking consecutive pieces
    int dx[] = {1, 0, 1, 1}; // Right, Down,Backward Diagonal, Forward DIagonal
    int dy[] = {0, 1, 1, -1};
    std::string dirName[] = {"Col", "Row", "Backward Diagonal", "Forward Diagonal"};
    // Iterate through each direction
    char enemyPiece = computerPlayer->getColor() == 'W' ? 'B' : 'W';
    int sureCaptureCount = 0; // stores the number of captures from that empty position
    for (int direction = 0; direction < 4; direction++)
    {
        // check left from the empty space

        if (board->isWithinBounds(row - dx[direction], col - dy[direction]) && board->getPiece(row - dx[direction], col - dy[direction]) == enemyPiece && board->isWithinBounds(row - dx[direction] * 2, col - dy[direction] * 2) && board->getPiece(row - dx[direction] * 2, col - dy[direction] * 2) == enemyPiece)
        {
            // sure capture
            if (board->isWithinBounds(row - dx[direction] * 3, col - dy[direction] * 3) && board->getPiece(row - dx[direction] * 3, col - dy[direction] * 3) == computerPlayer->getColor())
            {
                sureCaptureCount++;
                reason = reason + "Capture a pair to left " + dirName[direction] + ". ";
                if (r->getPairsCapturedNum(computerPlayer) < 4)
                {
                    priority = std::max(priority, 10);
                }
                else
                { // with this capture, the game ends
                    Player *opponent = r->getCurrentPlayer() == computerPlayer ? r->getNextPlayer() : computerPlayer;
                    int opponentScore = t->getTotalScores(opponent);
                    int ownScore = t->getTotalScores(computerPlayer);
                    if ((opponentScore - ownScore) > 1) // if opponent is winning by more than 1 points then we do not want to end the game just yet by capturing
                                                        // because we wont be able to win with that
                    {
                        priority = std::max(priority, 1);
                    }
                    else
                    {
                        /*if ((ownScore - opponentScore) > 3) {
                            priority = std::max(priority, 8);
                        }
                        else {
                            priority = std::max(priority, 6);
                        }*/
                        priority = std::max(priority, 8);
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
                    reason = reason + "Possibly Capture a pair to left " + dirName[direction] + ". ";
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
                sureCaptureCount++;
                reason = reason + "Capture a pair to right " + dirName[direction] + ". ";
                // if (r->getPairsCapturedNum(computerPlayer) < 4) {
                //     priority = std::max(priority, 10);
                // }

                // if (r->getPairsCapturedNum(computerPlayer) == 4)
                //{
                //
                //     Player* opponent = r->getCurrentPlayer() == computerPlayer ? r->getNextPlayer() : computerPlayer;
                //     int opponentScore = t->getTotalScores(opponent);
                //     int ownScore = t->getTotalScores(computerPlayer);
                //     if ((opponentScore - ownScore) > 0) //if opponent is winning by more than 1 points then we do not want to end the game just yet by capturing
                //         //because we wont be able to win with that
                //     {
                //         priority = std::max(priority, 1);
                //     }
                //     else
                //     {

                //        /*if ((ownScore - opponentScore) > 3) {
                //            priority = std::max(priority, 8);
                //        }
                //        else {
                //            priority = std::max(priority, 6);
                //        }*/
                //        priority = std::max(priority, 8);

                //    }
                //}
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
                    reason = reason + "Possibly Capture a pair to right " + dirName[direction] + ". ";
                    priority = std::max(priority, 6); // there is a chance that it may get captured and that should be higher priority then no capture
                    // that may lead to 4 consecutives in future;
                }
            }
        }
    }

    // if sureCaptureCount + r->getCapturedPairs(p) is > 4
    // then we consider two cases , winning or losing
    // if winning , winning by more than 3 ? then proceed with the surecapture , else hold off capturing
    // if losing, losing by more than surecapturCount? if yes, then dont put the piece there, else chance of winning so take it
    if (sureCaptureCount + r->getPairsCapturedNum(computerPlayer) > 4)
    {
        Player *opponent = r->getCurrentPlayer() == computerPlayer ? r->getNextPlayer() : computerPlayer;
        int opponentScore = t->getTotalScores(opponent);
        int ownScore = t->getTotalScores(computerPlayer);

        if ((ownScore - opponentScore) >= 0 && (ownScore - opponentScore) < 3)
        {                 // winning but the score difference is not high enough
            priority = 5; // decrease the priority, we wanna delay winning , focus on getting points by consecutive
        }
        else
        {
            if ((opponentScore - ownScore) > sureCaptureCount)
            {
                priority = -1; // no way you should place the piece there because even tho you will get the points, you will lose the game
            }
        }
    }
    else
    { // capture count for the player is not going to >= 5, so take the points
        // high priority
        if (sureCaptureCount > 0)
        {
            priority = std::max(priority, 10 * sureCaptureCount);
        }
        else
        {

            // what if placing the piece at the empty position leads to me getting sure captured
            //  see if by placing your piece there you are setting yourself for capture or not
            // consider 2 or 3 position
            // check for 1 and 4 positions for enemy pieces
            char ownPiece = computerPlayer->getColor();

            // it does not make sense to check the following code if this function is being called from enemy perspective
            // it is currently your turn, then enemy piece does not need to check if the enemy piece gets captured by placing its piece
            // at 2 or 3 position
            // when calling this function from enemy perspective, it should only care about whether the enemy can capture my pairs, if
            // the enemy places its piece there
            // if it can capture, then i should do my best to avoid it by placing my piece there

            if (checkingOwn)
            {
                for (int direction = 0; direction < 4; direction++)
                {
                    // empty position is in 2nd position, E is enemy, P is currentPlayer
                    // E_P_
                    if (board->isWithinBounds(row - dx[direction], col - dy[direction]) && board->getPiece(row - dx[direction], col - dy[direction]) == enemyPiece &&
                        board->isWithinBounds(row + dx[direction], col + dy[direction]) && board->getPiece(row + dx[direction], col + dy[direction]) == ownPiece &&
                        board->isWithinBounds(row + 2 * dx[direction], col + 2 * dy[direction]) && board->getPiece(row + 2 * dx[direction], col + 2 * dy[direction]) == '0')
                    {
                        priority = -15;
                        reason = "will get captured. dont place there\n";
                    }
                    //__PE
                    if (board->isWithinBounds(row + 2 * dx[direction], col + 2 * dy[direction]) && board->getPiece(row + 2 * dx[direction], col + 2 * dy[direction]) == enemyPiece &&
                        board->isWithinBounds(row + dx[direction], col + dy[direction]) && board->getPiece(row + dx[direction], col + dy[direction]) == ownPiece &&
                        board->isWithinBounds(row - dx[direction], col - dy[direction]) && board->getPiece(row - dx[direction], col - dy[direction]) == '0')
                    {
                        priority = -15;

                        reason = "will get captured. dont place there\n";
                    }
                    //_P_E
                    if (board->isWithinBounds(row - dx[direction], col - dy[direction]) && board->getPiece(row - dx[direction], col - dy[direction]) == ownPiece &&
                        board->isWithinBounds(row + dx[direction], col + dy[direction]) && board->getPiece(row + dx[direction], col + dy[direction]) == enemyPiece &&
                        board->isWithinBounds(row - 2 * dx[direction], col - 2 * dy[direction]) && board->getPiece(row - 2 * dx[direction], col - 2 * dy[direction]) == '0')
                    {
                        priority = -15;

                        reason = "will get captured. dont place there\n";
                    }

                    // EP__
                    if (board->isWithinBounds(row - dx[direction], col - dy[direction]) && board->getPiece(row - dx[direction], col - dy[direction]) == ownPiece &&
                        board->isWithinBounds(row + dx[direction], col + dy[direction]) && board->getPiece(row + dx[direction], col + dy[direction]) == '0' &&
                        board->isWithinBounds(row - 2 * dx[direction], col - 2 * dy[direction]) && board->getPiece(row - 2 * dx[direction], col - 2 * dy[direction]) == enemyPiece)
                    {
                        priority = -15;

                        reason = "will get captured. dont place there\n";
                    }
                }
            }
        }
    }

    if (r->getCurrentPlayer() != computerPlayer)
    {
        reason = "Stop opponent " + reason;
    }
    return {priority, reason};
}

std::pair<int, std::string> ComputerStrategy::calculatePriorityWith4Consectuives(int row, int col, Board *board, Player *computerPlayer, Round *r)
{
    int priority = 0;
    std::string reason = "";
    // Define directions for checking consecutive pieces
    int dx[] = {1, 0, 1, 1}; // Right, Down, Backward Diagonal, Forward Diagonal
    int dy[] = {0, 1, 1, -1};
    std::string dirName[] = {"Col", "Row", "Backward Diagonal", "Forward Diagonal"};
    int sure4ConsCount = 0;
    bool tessera = false;
    int tesseraCount = 0;
    // Iterate through each direction
    for (int direction = 0; direction < 4; ++direction)
    {

        bool isConsecutive = true;
        int leftCount = 0;
        int rightCount = 0;
        // determine consecutive count in left side
        while (isConsecutive)
        {
            int newRow = row - dx[direction] * (leftCount + 1);
            int newCol = col - dy[direction] * (leftCount + 1);
            if (board->isWithinBounds(newRow, newCol) && board->getPiece(newRow, newCol) == computerPlayer->getColor())
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
            if (board->isWithinBounds(newRow, newCol) && board->getPiece(newRow, newCol) == computerPlayer->getColor())
            {
                rightCount++;
            }
            else
            {
                isConsecutive = false;
            }
        }

        if (leftCount + rightCount == 3)
        {
            // sure 4 consecutive
            sure4ConsCount++;
            reason = reason + "Have 4 consecutive in " + dirName[direction] + ". ";
            // check for tessera formation
            if (board->getPiece(row - dx[direction] * (leftCount + 1), col - dy[direction] * (leftCount + 1)) == '0' &&
                board->getPiece(row + dx[direction] * (rightCount + 1), col + dy[direction] * (rightCount + 1)) == '0')
            {
                tessera = true;
                tesseraCount++;
            }
        }
    }

    priority = sure4ConsCount * 10;
    if (tessera)
    {
        priority += tesseraCount * 10;
        reason = reason + "Have Tessera Formation.";
    }
    if (r->getCurrentPlayer() != computerPlayer)
    {
        reason = "Stop opponent " + reason;
    }
    return {priority, reason};
}

std::pair<int, std::string> ComputerStrategy::calculateOpponentPriorityWith4Consectuives(int row, int col, Board *board, Player *opponentPlayer, Round *r)
{
    // TODO maybe i should do this withing the calculatePriorityWith4Consectuives function rather than creating a separate function

    return calculatePriorityWith4Consectuives(row, col, board, opponentPlayer, r);
}

std::pair<int, std::string> ComputerStrategy::calculatePriorityWith3Consectuives(int row, int col, Board *board, Player *computerPlayer, Round *r)
{
    int priority = 0;
    std::string reason = "";
    // Define directions for checking consecutive pieces
    int dx[] = {1, 0, 1, 1}; // Right, Down, Backward Diagonal, Forward Diagonal
    int dy[] = {0, 1, 1, -1};
    std::string dirName[] = {"Col", "Row", "Backward Diagonal", "Forward Diagonal"};
    int sure3ConsCount = 0;
    bool oneOpenEnd = false, bothOpenEnds = false;
    // Iterate through each direction
    for (int direction = 0; direction < 4; ++direction)
    {

        bool isConsecutive = true;
        int leftCount = 0;
        int rightCount = 0;
        // determine consecutive count in left side
        while (isConsecutive)
        {
            int newRow = row - dx[direction] * (leftCount + 1);
            int newCol = col - dy[direction] * (leftCount + 1);
            if (board->isWithinBounds(newRow, newCol) && board->getPiece(newRow, newCol) == computerPlayer->getColor())
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
            if (board->isWithinBounds(newRow, newCol) && board->getPiece(newRow, newCol) == computerPlayer->getColor())
            {
                rightCount++;
            }
            else
            {
                isConsecutive = false;
            }
        }

        if (leftCount + rightCount == 2)
        {
            // sure 3 consecutive
            sure3ConsCount++;

            // check for possibility of growing into 4 in either side

            if (board->getPiece(row - dx[direction] * (leftCount + 1), col - dy[direction] * (leftCount + 1)) == '0' &&
                board->getPiece(row + dx[direction] * (rightCount + 1), col + dy[direction] * (rightCount + 1)) == '0')
            {
                reason = reason + "Have 3 consecutive in " + dirName[direction] + " with both ends open, ";
                bothOpenEnds = true;
            }
            else if (board->getPiece(row - dx[direction] * (leftCount + 1), col - dy[direction] * (leftCount + 1)) == '0')
            {
                reason = reason + "Have 3 consecutive in " + dirName[direction] + " with one open end, ";
                oneOpenEnd = true;
            }
            else if (board->getPiece(row + dx[direction] * (rightCount + 1), col + dy[direction] * (rightCount + 1)) == '0')
            {
                reason = reason + "Have 3 consecutive in " + dirName[direction] + " with one open end, ";
                oneOpenEnd = true;
            }
        }
    }

    if (oneOpenEnd)
    {
        priority = sure3ConsCount * 4;
    }
    if (bothOpenEnds)
    {
        priority = sure3ConsCount * 6;
    }
    if (r->getCurrentPlayer() != computerPlayer)
    {
        reason = "Stop opponent " + reason;
    }
    return {priority, reason};
}

std::pair<int, std::string> ComputerStrategy::calculateOpponentPriorityWith3Consectuives(int row, int col, Board *board, Player *opponentPlayer, Round *r)
{
    return calculatePriorityWith3Consectuives(row, col, board, opponentPlayer, r);
}

std::pair<int, std::string> ComputerStrategy::calculatePriorityWith2Consectuives(int row, int col, Board *board, Player *computerPlayer, Round *r)
{
    int priority = 0;
    std::string reason = "";
    // Define directions for checking consecutive pieces
    int dx[] = {1, 0, 1, 1}; // Right, Down, Backward Diagonal, Forward Diagonal
    int dy[] = {0, 1, 1, -1};
    std::string dirName[] = {"Col", "Row", "Backward Diagonal", "Forward Diagonal"};
    int sure3ConsCount = 0;
    bool possibleCapture = false, bothOpenEnds = false;
    // Iterate through each direction
    for (int direction = 0; direction < 4; ++direction)
    {

        bool isConsecutive = true;
        int leftCount = 0;
        int rightCount = 0;
        // determine consecutive count in left side
        while (isConsecutive)
        {
            int newRow = row - dx[direction] * (leftCount + 1);
            int newCol = col - dy[direction] * (leftCount + 1);
            if (board->isWithinBounds(newRow, newCol) && board->getPiece(newRow, newCol) == computerPlayer->getColor())
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
            if (board->isWithinBounds(newRow, newCol) && board->getPiece(newRow, newCol) == computerPlayer->getColor())
            {
                rightCount++;
            }
            else
            {
                isConsecutive = false;
            }
        }

        if (leftCount + rightCount == 1)
        {
            // sure 3 consecutive
            sure3ConsCount++;

            // check for possibility of growing into 4 in either side, if one side is blocked by enemy, then dont put there

            if (board->getPiece(row - dx[direction] * (leftCount + 1), col - dy[direction] * (leftCount + 1)) == '0' &&
                board->getPiece(row + dx[direction] * (rightCount + 1), col + dy[direction] * (rightCount + 1)) == '0')
            {
                reason = reason + "Have 2 consecutive in " + dirName[direction] + " with both ends open, ";
                bothOpenEnds = true;
            }
            else if (board->getPiece(row - dx[direction] * (leftCount + 1), col - dy[direction] * (leftCount + 1)) == '0')
            {
                possibleCapture = true;
            }
            else if (board->getPiece(row + dx[direction] * (rightCount + 1), col + dy[direction] * (rightCount + 1)) == '0')
            {
                possibleCapture = true;
            }
        }
    }

    // if both ends are open
    // possibleCapture will be true if for any direction from that position, it leads to its capture
    if (!possibleCapture && bothOpenEnds)
    {
        priority = sure3ConsCount * 2;
    }
    if (r->getCurrentPlayer() != computerPlayer)
    {
        reason = "Stop opponent " + reason;
    }
    return {priority, reason};
}

std::pair<int, std::string> ComputerStrategy::calculateOpponentPriorityWith2Consectuives(int row, int col, Board *board, Player *opponentPlayer, Round *r)
{
    return calculatePriorityWith2Consectuives(row, col, board, opponentPlayer, r);
}

std::pair<int, std::string> ComputerStrategy::calculateEndGamePriorityWith5Consectuives(int row, int col, Board *board, Player *computerPlayer, Round *r)
{

    int priority = 0;
    std::string reason = "";
    // Define directions for checking capture pairs
    int dx[] = {1, 0, 1, 1}; // Right, Down,Backward Diagonal, Forward DIagonal
    int dy[] = {0, 1, 1, -1};
    std::string dirName[] = {"Col", "Row", "Backward Diagonal", "Forward Diagonal"};
    int fiveConsCount = 0;
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
            fiveConsCount++;
            // if opponent score is significantly higher and if you have a chance to get 5 consecutive for sure, then take it
            // it does not make sense to wait for getting more points as at any point enemy can end the game and even further the score gap
            Player *opponent = r->getCurrentPlayer() == computerPlayer ? r->getNextPlayer() : computerPlayer;
            int opponentScore = t->getTotalScores(opponent);
            int ownScore = t->getTotalScores(computerPlayer);

            reason = reason + " Have 5 consecutives in " + dirName[direction] + ". ";
            // if you are winning by major difference then not that important...delay winning
            if ((ownScore - opponentScore) > 5)
            {

                // the max consecutive there can be is 9, and winning by having 9 consecutive is a great loss,
                // as we wont be able to get points for two 4 consecutives, 9 = 4_4
                if (leftCount + rightCount >= 8)
                {
                    priority = std::max(priority, 4);
                }
                else
                {
                    priority = std::max(priority, 8);
                }
            }

            else
            {
                priority = std::max(priority, 20);
            }
        }
    }
    priority = priority + 10 * (fiveConsCount - 1); // one five cons will end the game and others can be used for getting points as
    // 4 consecutives
    if (r->getCurrentPlayer() != computerPlayer)
    {
        reason = "Stop opponent " + reason;
    }

    return {priority, reason};
}

std::pair<int, std::string> ComputerStrategy::calculateOpponentsEndGamePriorityWith5Consectuives(int row, int col, Board *board, Player *opponentPlayer, Round *r)
{
    // TODO maybe i should do this within the calculateEndGamePriorityWith5Consectuives function rather than creating a separate function

    return calculateEndGamePriorityWith5Consectuives(row, col, board, opponentPlayer, r);
}

std::pair<int, std::string> ComputerStrategy::calculateStopOpponentPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer)
{
    // determine the priority for human player
    // put the computer piece in that max priority position

    std::pair<int, std::string> priorityPair = calculateConsecutivesPriority(row, col, board, humanPlayer);
    priorityPair.second = "Stop Opponent " + priorityPair.second;
    return priorityPair;
}

std::pair<int, std::string> ComputerStrategy::calculateCaptureRiskPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer, Round *r)
{
    // TODO maybe i should do this withing the calculateCapturePairsPriority function rather than creating a separate function

    // see from enemy's viewpoint, if for that position, if enemy places its piece, what damage will it do..will it capture my pairs
    return calculateCapturePairsPriority(row, col, board, humanPlayer, r, false);
}

std::string ComputerStrategy::convertPosToString(int row, int col)
{

    // col t0 Alphabet equivalent
    // col starts from 1 to 19
    char colAlphabet = 'A' + col - 1;
    std::string rowString = std::to_string(20 - row); // because row label is inverted
    std::string inputString = colAlphabet + rowString;

    return inputString;
}

std::string ComputerStrategy::determineBestPosition(Board *board, Player *computerPlayer, Player *humanPlayer, Round *r)
{
    int maxPriority = -1;
    int bestRow = -1, bestCol = -1;
    int boardSize = 20;
    std::string finalReason = "";
    int boardPriority[20][20] = {0};
    for (int row = 1; row < boardSize; row++)
    {
        for (int col = 1; col < boardSize; col++)
        {
            if (board->getPiece(row, col) == '0')
            {

                // if it is second turn , White, and within 3 steps from center
                // set priority to negative...we dont wanna put out piece there
                if (r->getTurnNum() == 2 && abs(row - 10) <= 3 && abs(col - 10) <= 3)
                {
                    boardPriority[row][col] = -1;
                    continue;
                }

                // store the pairs in a vector
                // iterate through the vector to get the maximum priority and the corresponding result for that empty space
                std::vector<std::pair<int, std::string>> results;
                results.push_back(calculateCapturePairsPriority(row, col, board, r->getCurrentPlayer(), r));                   // 0
                results.push_back(calculateCapturePairsPriority(row, col, board, r->getCurrentPlayer(), r));                   // 1
                results.push_back(calculateEndGamePriorityWith5Consectuives(row, col, board, r->getCurrentPlayer(), r));       // 2
                results.push_back(calculateOpponentsEndGamePriorityWith5Consectuives(row, col, board, r->getNextPlayer(), r)); // 3, *2
                results.push_back(calculatePriorityWith4Consectuives(row, col, board, r->getCurrentPlayer(), r));              // 4
                results.push_back(calculateOpponentPriorityWith4Consectuives(row, col, board, r->getNextPlayer(), r));         // 5
                results.push_back(calculatePriorityWith3Consectuives(row, col, board, r->getCurrentPlayer(), r));              // 4
                results.push_back(calculateOpponentPriorityWith3Consectuives(row, col, board, r->getNextPlayer(), r));         // 5
                results.push_back(calculatePriorityWith2Consectuives(row, col, board, r->getCurrentPlayer(), r));              // 4
                results.push_back(calculateOpponentPriorityWith2Consectuives(row, col, board, r->getNextPlayer(), r));         // 5

                results.push_back(calculateStopOpponentPriority(row, col, board, r->getCurrentPlayer(), r->getNextPlayer()));   // 6
                results.push_back(calculateCaptureRiskPriority(row, col, board, r->getCurrentPlayer(), r->getNextPlayer(), r)); // 7
                int maxPForThisSpace = -1;
                std::string maxReason = "";
                for (int i = 0; i <= results.size() - 1; i++)
                {
                    int p = results[i].first;
                    if (i == 2 || i == 3)
                    {
                        p *= 2; // give double priority to stop opponent from getting the game points
                    }
                    if (p > maxPForThisSpace)
                    {
                        maxPForThisSpace = p;
                        maxReason = results[i].second;
                    }
                }
                boardPriority[row][col] = maxPForThisSpace;
                if (maxPriority < maxPForThisSpace)
                {
                    maxPriority = maxPForThisSpace;
                    finalReason = maxReason;
                    bestRow = row;
                    bestCol = col;
                }
            }
        }
    }

    // shows priority of each empty cell
    /*for (int row = 1; row < boardSize; row++)
    {
        for (int col = 1; col < boardSize; col++)
        {
            std::cout << boardPriority[row][col] << " ";
        }
        std::cout << std::endl;
    }*/

    // Place the computer player's piece at (bestRow, bestCol)

    setFinalReason(finalReason);
    return convertPosToString(bestRow, bestCol);
}

std::string ComputerStrategy::getFinalReason()
{
    return this->bestReason;
}

void ComputerStrategy::setFinalReason(std::string reason)
{
    this->bestReason = reason;
}