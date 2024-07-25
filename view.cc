#include "headers/view.h"
#include "headers/floor.h"
#include "headers/humanPlayer.h"
using namespace std;

View::View() : action{""} {}

View::~View() {}

void View::render(const Floor& floor, const HumanPlayer& player, ostream& out) {
    // go through each row & column on board, includes border
    for (size_t row = 0; row < floor.board.size(); ++row) {
        for (size_t col = 0; col < floor.board[row].size(); ++col) {
            Cell& c = floor.board[row][col];
            if (c.occupant == nullptr) {
                // use cell type
                switch (c.cellType) {
                    case Cell::EMPTY:
                        out << ' ';
                        break;
                    case Cell::STAIRS:
                        if (floor.compassFound) {
                            out << '\\';
                            break;
                        }
                    case Cell::GROUND:
                        out << '.';
                        break;
                    case Cell::VWALL:
                        out << '|';
                        break;
                    case Cell::HWALL:
                        out << '-';
                        break;
                    case Cell::DOOR:
                        out << '+';
                        break;
                    case Cell::PASSAGE:
                        out << '#';
                        break;
                    default:
                        // throw error?
                        out << "missing CellType\n";
                }
            } else {
                // use occupant type
                out << c.occupant->charAt();
            }
        }
        out << '\n';
    }
    //output UI
    out << "Race: " << player.race;
    out << " Gold: " << player.gold;
    for (int i = 0; i < View::SPACING; ++i) out << ' ';
    out << "Floor: " << curFloor << '\n';

    out << "HP: " << player.hp << '\n';
    out << "Atk: " << player.atk << '\n';
    out << "Def: " << player.def << '\n';

    out << "Action: " << action << '\n';
}

