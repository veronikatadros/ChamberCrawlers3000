#include "headers/view.h"
#include "headers/floor.h"
#include "headers/player.h"
#include "headers/entity.h"
using namespace std;

View::View() : action{"default action"} {}

View::~View() {}

void View::render(const Floor* floor, const int curFloor, const Player* player, ostream& out) {
    // go through each row & column on board, includes border
    for (size_t row = 0; row < floor->board.size(); ++row) {
        for (size_t col = 0; col < floor->board[row].size(); ++col) {
            const Cell& c = floor->board[row][col];
            if (c.occupant == nullptr) {
                out << View::BEGCOLOR;
                // use cell type
                switch (c.cellType) {
                    case Cell::EMPTY:
                        out << "m ";
                        break;
                    case Cell::STAIRS:
                        // green (32)
                        if (player->hasCompass) {
                            out << "32m\\";
                            break;
                        }
                    case Cell::GROUND:
                        out << "m.";
                        break;
                    case Cell::VWALL:
                        // inverse (7)
                        out << "7m|";
                        break;
                    case Cell::HWALL:
                        // inverse (7)
                        out << "7m-";
                        break;
                    case Cell::DOOR:
                        // inverse (7) and then blue (34)
                        out << "7;34m+";
                        break;
                    case Cell::PASSAGE:
                        // inverse (7) and then cyan (36)
                        out << "7;36m#";
                        break;
                    default:
                        // throw error?
                        out << "missing CellType\n";
                }
                out << View::ENDCOLOR;
            } else {
                // use occupant type
                char temp = c.occupant->charAt();
                // enemy red (31)
                // potion blue (34)
                // player bold/bright (1) magenta (35)
                out << View::BEGCOLOR;
                switch (c.occupant->eType) {
                    case Entity::ENEMY:
                        out << "31m";
                        out << temp;
                        break;
                    case Entity::PLAYER:
                        out << "1;35m";
                        out << temp;
                        break;
                    case Entity::ITEM:
                        out << "34m";
                        out << temp;
                        break;
                    default:
                        // throw error?
                        out << "missing EntityType";
                }
                out << View::ENDCOLOR;
            }
        }
        out << '\n';
    }
    //output UI
    out << "Race: " << player->race;
    out << " Gold: " << player->gold;
    for (int i = 0; i < View::SPACING; ++i) out << ' ';
    out << "Floor: " << curFloor << '\n';

    out << "HP: " << player->hp << '\n';
    out << "Atk: " << player->atk << '\n';
    out << "Def: " << player->def << '\n';

    out << "Action: " << action << '\n';
}

