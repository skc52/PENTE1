#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Tournament.h"
#include "Round.h"
void gameLoop(Round *r, Board *b, Tournament *t, Player *h, Player *c);
int main()
{
    Tournament *tournament = new Tournament();
    // get the name of the human,
    std::string humanName = "samip";
    //   std::cout << "Enter your name: \n";
    //   std::cin >> humanName;
    std::cout << "Welcome to Pente, " << humanName << std::endl;
    // create the human class
    Player *human = new Human(humanName);
    // create the computer class
    std::string computerName = "ROBOT";
    Player *computer = new Computer(computerName);
    // create the board class
    Board *board = new Board();

    bool wishToContinue = true;
    while (wishToContinue)
    {
        Round *r = tournament->createANewRound();
        gameLoop(r, board, tournament, human, computer);
        wishToContinue = r->askToContinueGame();
    }

    // Tournament is over;
    tournament->displayScoresForAllRounds();
    tournament->showTotalScoresForBoth();
    tournament->announceWinner();

    return 0;
}

void gameLoop(Round *r, Board *b, Tournament *t, Player *h, Player *c)
{
    // start the round
    r->startRound(t, b);
    bool gameEnded = false;
    while (!gameEnded)
    {
        r->changeTurn();
        r->askPositionInput(b);
        // game won check?
        if (!r->getCurrentPlayer()->makeMove(r, b))
        {
            gameEnded = true;
        }
        b->DisplayBoard(r);
    }
    r->displayClosingStats();
    r->announceWinnerOfTheRound();
}