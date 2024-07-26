#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char *argv[]){

    string command;
    string dir;
    Game game(argc > 1 ? argv[1] : "");

    cout << "Welcome to the game of CC3k!\n";
    cout << "Enter 'q' to quit, or any other character to continue: ";

    game.start();
    

}