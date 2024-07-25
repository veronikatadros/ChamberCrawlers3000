#include "headers/humanPlayer.h"

HumanPlayer& HumanPlayer::getInstance() {
    static HumanPlayer instance;  // Static instance of HumanPlayer
    return instance;
}
