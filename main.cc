#include <curses.h>
#include <iostream>
#include "headers/game.h"
#include "headers/randomNumberGenerator.h"

using namespace std;

int main(int argc, char *argv[]){
    RandomNumberGenerator();    
    
    string cmd = argc > 1 ? argv[1] : "";
    cout << "using ncurses? Y/N: ";
    char answer;
    cin >> answer;
    cout << '\n';
    Game* game;
    bool usingNcurses;
    if (answer == 'Y') {
        setlocale(LC_ALL, "");
        initscr();              // Initialize the window
        raw();                  // Line buffering disabled
        keypad(stdscr, TRUE);   // Enable special keys capture
        noecho();               // Don't echo while we do getch
        start_color();          // Start color functionality

        // Initialize colors if you plan to use them
        init_pair(1, COLOR_MAGENTA, COLOR_BLACK);       // Example: red text
        init_pair(2, COLOR_WHITE, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_RED, COLOR_BLACK);
        init_pair(6, COLOR_CYAN, COLOR_BLACK);
        init_pair(7, COLOR_BLACK, COLOR_WHITE);
        init_pair(8, COLOR_GREEN, COLOR_BLACK);
        init_pair(9, COLOR_WHITE, COLOR_GREEN);
        usingNcurses = true;
    } else {
        usingNcurses = false;
    }
    game = new Game(cmd, usingNcurses);
    game->start();

    while(game->playAgain) {
        delete game;
        game = new Game(cmd, usingNcurses);
        game->start();
    }
    delete game;

    endwin();
}