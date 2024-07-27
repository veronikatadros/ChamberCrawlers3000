#include <iostream>
#include "headers/game.h"
#include "headers/randomNumberGenerator.h"

using namespace std;

int main(int argc, char *argv[]){

    string command;
    string dir;
    RandomNumberGenerator(0);
    Game game(argc > 1 ? argv[1] : "");

    game.start();
}