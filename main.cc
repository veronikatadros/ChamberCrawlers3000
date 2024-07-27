#include <iostream>
#include "headers/game.h"

using namespace std;

int main(int argc, char *argv[]){

    string command;
    string dir;
    Game game(argc > 1 ? argv[1] : "");

    game.start();
}