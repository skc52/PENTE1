#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Tournament.h"
#include "ComputerStrategy.h"
#include "Round.h"
void gameLoop(Round *r, Board *b, Player *human, Player *computer, Tournament *t, ComputerStrategy *c, bool &unpause);
int main()
{
    Tournament *tournament = new Tournament();
    // get the name of the human,
    std::string humanName = "Human";
    std::cout << "Welcome to Pente, " << humanName << std::endl;
    // create the human class
    Player *human = new Human(humanName);
    // create the computer class
    std::string computerName = "ROBOT";
    Player *computer = new Computer(computerName);
    // setup players for tournament
    tournament->setUpPlayers(human, computer);
    // create the board class
    Board *board = new Board();
    // create Computer strategy object
    ComputerStrategy *c = new ComputerStrategy(tournament);

    // ask if the user wants to load a game
    char loader;
    std::cout << "Do you want to load a game? Enter y/Y for yes or n/N for no\n";

    do
    {
        std::cin >> loader;
        loader = std::tolower(loader); // Convert the input character to lowercase
    } while (loader != 'y' && loader != 'n');

    bool wishToContinue = true;
    bool unpause = false;
    while (wishToContinue)
    {
        Round *r = tournament->createANewRound();
        if (loader == 'y')
        {
            std::string filename;
            std::cout << "Enter the name of the file that you wanna load game from\n";
            std::cin >> filename;

            // if filename does not have .txt extension, add it
            if (filename.substr(filename.size() - 1 - 3) != ".txt")
            {
                filename += ".txt";
            }

            if (!tournament->LoadGame(filename, board, r))
            {
                return 1;
            }

            // set current player
            r->loadRound(filename, human, computer, tournament);
            // r->getCurrentPlayer()->makeMove(r, board, c, tournament);

            loader = 'n';
            unpause = true;
        }
        else
        {
            // start the round
            r->startRound(tournament, board);
        }
        gameLoop(r, board, human, computer, tournament, c, unpause);
        if (!tournament->getPause())
        {
            wishToContinue = r->askToContinueGame();
        }
        else
        {
            wishToContinue = false;
        }
    }

    // Tournament is over;
    if (!tournament->getPause())
    {
        tournament->displayScoresForAllRounds();
        tournament->showTotalScoresForBoth();
        tournament->announceWinner();
    }

    return 0;
}

void gameLoop(Round *r, Board *b, Player *human, Player *computer, Tournament *t, ComputerStrategy *c, bool &unpause)
{
    // r->startRound(t, b);
    b->DisplayBoard(r);
    bool gameEnded = false;
    bool gamePaused = false;
    while (!gameEnded)
    {
        r->changeTurn(b, human, computer, t);

        unpause = false;

        // r->askPositionInput(b);
        // game won check?
        if (!r->getCurrentPlayer()->makeMove(r, b, c, t))
        {
            gameEnded = true;
        }
        if (!t->getPause())
        {
            b->DisplayBoard(r);
        }
    }

    // display scores for both round and the overall tournament
    if (!t->getPause())
    {
        r->displayClosingStats();
        t->showTotalScoresForBoth();
    }
}