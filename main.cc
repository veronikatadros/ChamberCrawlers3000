#include <iostream>
#include "headers/game.h"
#include "headers/randomNumberGenerator.h"

using namespace std;

int main(int argc, char *argv[]){

    string command;
    string dir;
    RandomNumberGenerator();    
    
    string cmd = argc > 1 ? argv[1] : "";
    Game* game = new Game(cmd);
    game->start();

    while(game->playAgain) {
        delete game;
        game = new Game(cmd);
        game->start();
    }
    delete game;
}