#include <curses.h>
#include <iostream>
#include "headers/game.h"
#include "headers/randomNumberGenerator.h"

using namespace std;

int main(int argc, char *argv[]){

    initscr();          // Start curses mode
    cbreak();           // Line buffering disabled
    raw();
    noecho();           // Don't echo() while we do getch
    keypad(stdscr, TRUE); // Enable F1, F2 etc., and arrow keys

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

    endwin();
}