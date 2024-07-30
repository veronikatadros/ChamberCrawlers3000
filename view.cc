#include "headers/view.h"
#include "headers/floor.h"
#include "headers/player.h"
#include "headers/enemy.h"
#include "headers/item.h"
#include "headers/items/gold.h"
#include "headers/items/goldHoard.h"
#include "headers/items/potion.h"
#include "headers/items/timedPotion.h"
#include <iostream>
#include <sstream>
using namespace std;

View::View() : action{""} {}

View::~View() {}

void View::render(const Floor* floor, const int curFloor, const Player* player) {
    // go through each row & column on board, includes border
    for (size_t row = 0; row < floor->board.size(); ++row) {
        for (size_t col = 0; col < floor->board[row].size(); ++col) {
            const Cell& c = floor->board[row][col];
            string output = "";
            if (c.occupant == nullptr) {
                output += View::BEGCOLOR;
                // use cell type
                switch (c.cellType) {
                    case Cell::EMPTY:
                        output += "m ";
                        break;
                    case Cell::STAIRS:
                        // green (32)
                        if (player->hasCompass) {
                            output += "32m\\";
                            break;
                        }
                    case Cell::GROUND:
                        output += "m.";
                        break;
                    case Cell::VWALL:
                        // inverse (7)
                        output += "7m|";
                        break;
                    case Cell::HWALL:
                        // inverse (7)
                        output += "7m-";
                        break;
                    case Cell::DOOR:
                        // inverse (7) and then blue (34)
                        output += "7;34m+";
                        break;
                    case Cell::PASSAGE:
                        // blue (34)
                        output += "34m#";
                        break;
                    default:
                        // throw error?
                        output += "missing CellType\n";
                }
                output += View::ENDCOLOR;
            } else {
                // use occupant type
                char temp = c.occupant->charAt();
                // enemy red (31)
                // potion blue (34)
                // player bold/bright (1) magenta (35)
                output += View::BEGCOLOR;
                switch (c.occupant->eType) {
                    case Entity::ENEMY:
                        output += "31m";
                        output += temp;
                        break;
                    case Entity::PLAYER:
                        output += "1;35m";
                        output += temp;
                        break;
                    case Entity::ITEM: {
                        if (temp == 'G') {
                            output += "33m";
                        } else if (temp == 'P') {
                            output += "34m";
                        } else {
                            output += "35m";
                        }
                        output += temp;
                        break;
                    } 
                    default:
                        // throw error?
                        output += "missing EntityType";
                }
                output += View::ENDCOLOR;
            }
            cout << output;
        }
        cout << '\n';
    }
    //output UI
    cout << "Race: " << player->race;
    for (int i = 0; i < View::SPACING; ++i) cout << ' ';
    cout << "Floor: " << curFloor + 1 << '\n';
    
    cout << "Gold: " << player->gold << '\n';

    cout << "HP: " << player->hp << '\n';
    cout << "Atk: " << player->atk << '\n';
    cout << "Def: " << player->def << '\n';

    cout << "Action: " << action << '\n';
    action = "";
}

void View::enemyAttack(Enemy* enemy) {
    char e = enemy->charAt();
    getEnemyName(e);
    action += " tries to attack! ";
}

void View::playerAttack(Enemy* enemy, bool dead) {
    action += "Player ";
    if (dead) {
        action += "kills ";
    } else {
        action += "attacks ";
    }
    char e = enemy->charAt();
    getEnemyName(e);
    if (!dead) {
        action += " (" + to_string(enemy->hp);
        action += " HP)";
    }
    action += "! ";
}

void View::playerMove(string dir) {
    action += "Player moves " + dir + "! ";
}

void View::itemBought(Item* item, bool tooBroke) {
    stringstream stream;
    stream << "Player bought ";
    Potion* p = dynamic_cast<Potion*>(item);
    if (tooBroke) {
        stream << "nothing, you broke. ";
        action += stream.str();
        return;
    } else if (!p) {
        stream << "nothing, merchant does not sell that. ";
        action += stream.str();
        return;
    }
    stream << "potion ";
    if (p->stat == "HP") {
        TimedPotion* tp = dynamic_cast<TimedPotion*>(p);
        if (tp) {
            stream << ((tp->value >= 0) ? "of regeneration! +" : "of poison! -");
            stream << tp->value << "HP/turn ";
            action += stream.str();
            return;
        } else {
            stream << ((p->value >= 0) ? "of health! +" : "of pain! -");
        }
    } else if (p->stat == "ATK") {
        stream << ((p->value >= 0) ? "of strength! +" : "of weakness! -");
    } else if (p->stat == "DEF") {
        stream << ((p->value >= 0) ? "of shielding! +" : "of rust! -");
    }
    int value = abs(p->value);
    stream << value;
    stream << " " << p->stat << " ";
    action += stream.str();
}

void View::itemGrabbed(Item* item) {
    stringstream stream;
    stream << "Player picks up";
    switch(item->itemType) {
        case (Item::GOLD): {
            stream << " Gold (";
            Gold* g = dynamic_cast<Gold*>(item);
            stream << g->value;
            stream << ")! ";
            break;
        }
        case (Item::GOLD_HOARD): {
            action += " Gold Hoard (";
            GoldHoard* g = dynamic_cast<GoldHoard*>(item);
            stringstream stream;
            stream << g->value;
            stream << ")! ";
            break;
        }
        case (Item::POTION): {
            stream << " potion ";
            Potion* p = dynamic_cast<Potion*>(item);
            
            if (p->stat == "HP") {
                TimedPotion* tp = dynamic_cast<TimedPotion*>(p);
                if (tp) {
                    stream << ((tp->value >= 0) ? "of regeneration! +" : "of poison! -");
                    stream << tp->value << "HP/turn ";
                    break;
                } else {
                    stream << ((p->value >= 0) ? "of health! +" : "of pain! -");
                }
            } else if (p->stat == "ATK") {
                stream << ((p->value >= 0) ? "of strength! +" : "of weakness! -");
            } else if (p->stat == "DEF") {
                stream << ((p->value >= 0) ? "of shielding! +" : "of rust! -");
            }
            int value = abs(p->value);
            stream << value;
            stream << " " << p->stat << " ";
            break;
        }
        case (Item::COMPASS): {
            stream << " Compass! Stairs to next floor visible. ";
            break;
        }
        case (Item::BARRIER_SUIT): {
            stream << " Barrier Suit! Damage done to player halved. ";
            break;
        }
        default:
            break;
    }
    action += stream.str();
}

void View::gameOver() {
    cout << R"(
|-----------------------------------------------------------------------------|
|                                                                             |
|                                                                             |
|                                                                             |
|          ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓██████████████▓▒░░▒▓████████▓▒░        |
|         ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░               |
|         ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░               |
|         ░▒▓█▓▒▒▓███▓▒░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓██████▓▒░          |
|         ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░               |
|         ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░               |
|          ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░        |
|                                                                             |
|                                                                             |
|                                                                             |
|             ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓███████▓▒░             |
|            ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░            |
|            ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░            |
|            ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓██████▓▒░ ░▒▓███████▓▒░             |
|            ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░            |
|            ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░            |
|             ░▒▓██████▓▒░   ░▒▓██▓▒░  ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░            |
|                                                                             |
|                                                                             |
|                                                                             |
|-----------------------------------------------------------------------------|





...Press r to restart or q to quit
    )" << '\n';
}

void View::gameWon(Player* p) {
    float score = p->gold;
    if (p->race == "Human") {
        score *= 1.5;
    }
    
    cout << R"(
|-----------------------------------------------------------------------------|
|                                                                             |
|                                                                             |
|                                                                             |
|         ██████╗██╗  ██╗ █████╗ ███╗   ███╗██████╗ ███████╗██████╗           |
|        ██╔════╝██║  ██║██╔══██╗████╗ ████║██╔══██╗██╔════╝██╔══██╗          |
|        ██║     ███████║███████║██╔████╔██║██████╔╝█████╗  ██████╔╝          |
|        ██║     ██╔══██║██╔══██║██║╚██╔╝██║██╔══██╗██╔══╝  ██╔══██╗          |
|        ╚██████╗██║  ██║██║  ██║██║ ╚═╝ ██║██████╔╝███████╗██║  ██║          |
|         ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝          |
|                                     ^                                       |
|                                    <*>                                      |
|                                     v                                       |
|                                                                             |
|         ██████╗██████╗  █████╗ ██╗    ██╗██╗     ███████╗██████╗ ██╗        |
|        ██╔════╝██╔══██╗██╔══██╗██║    ██║██║     ██╔════╝██╔══██╗██║        |
|        ██║     ██████╔╝███████║██║ █╗ ██║██║     █████╗  ██║  ██║██║        |
|        ██║     ██╔══██╗██╔══██║██║███╗██║██║     ██╔══╝  ██║  ██║╚═╝        |
|        ╚██████╗██║  ██║██║  ██║╚███╔███╔╝███████╗███████╗██████╔╝██╗        |
|         ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚══╝╚══╝ ╚══════╝╚══════╝╚═════╝ ╚═╝        |
|                                                                             |
|                                                                             |
|                                                                             |
|                                                                             |
|-----------------------------------------------------------------------------|
    )" << '\n';
    cout << "Score: " << score << endl;
    cout << "\n\n\n\n";
    cout << "...Press r to restart or q to quit\n";
}

void View::invalidActionCommand() {
    action += "Invalid command, please try again!";
}

void View::invalidCommand() {
    cout << "Invalid command. Try again!\n";
}

void View::gameStart() {
    cout << "Welcome to the game of CC3k!\n";
    cout << "Enter 'q' to quit or please enter your race: ";
}

void View::input() {
    cout << "Please input command: ";
}

void View::getEnemyName(char enemyChar) {
    switch (enemyChar) {
        case 'V':
            action += "Vampire";
            break;
        case 'W':
            action += "Werewolf";
            break;
        case 'N':
            action += "Goblin";
            break;
        case 'M':
            action += "Merchant";
            break;
        case 'D':
            action += "Dragon";
            break;
        case 'X':
            action += "Phoenix";
            break;
        case 'T':
            action += "Troll";
            break;
        default:
            break;
    }
}
