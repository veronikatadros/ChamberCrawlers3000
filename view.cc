#include "headers/view.h"
#include "headers/floor.h"
#include "headers/player.h"
#include "headers/enemy.h"
#include "headers/item.h"
using namespace std;

View::View() : action{"default action"} {}

View::~View() {}

void View::render(const Floor* floor, const int curFloor, const Player* player, ostream& out) {
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
            out << output;
        }
        out << '\n';
    }
    //output UI
    out << "Race: " << player->race;
    for (int i = 0; i < View::SPACING; ++i) out << ' ';
    out << "Floor: " << curFloor + 1 << '\n';
    
    out << "Gold: " << player->gold << '\n';

    out << "HP: " << player->hp << '\n';
    out << "Atk: " << player->atk << '\n';
    out << "Def: " << player->def << '\n';

    out << "Action: " << action << '\n';
    action = "";
}

void View::enemyAttack(Enemy* enemy) {
    // get enemy type
    char e = enemy->charAt();
    switch (e) {
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
    action += " attacks! ";
}

void View::playerAttack(Enemy* enemy, bool dead) {
    // get enemy type
    action += "Player attacks ";
    char e = enemy->charAt();
    switch (e) {
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

    action += " (" + enemy->hp;
    action += " HP)! ";
}

void View::playerMove(string dir) {
    action += "Player moves " + dir + " ";
}

void View::itemGrabbed(Entity* item) {
    
}

