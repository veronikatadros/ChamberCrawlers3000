#include "headers/view.h"
#include "headers/floor.h"
#include "headers/player.h"
#include "headers/enemy.h"
#include "headers/item.h"
#include "headers/items/gold.h"
#include "headers/items/goldHoard.h"
#include "headers/items/potion.h"
#include <iostream>
#include <sstream>
#include <curses.h>

using namespace std;

View::View() : action{""} {}

View::~View() {}

void View::render(const Floor* floor, const int curFloor, const Player* player) {
    clear(); // Clear the screen

    for (size_t row = 0; row < floor->board.size(); ++row) {
        for (size_t col = 0; col < floor->board[row].size(); ++col) {
            const Cell& c = floor->board[row][col];
            if (c.occupant == nullptr) {
                switch (c.cellType) {
                    case Cell::EMPTY:
                        break;
                    case Cell::STAIRS:
                        if (player->hasCompass) {
                            attron(COLOR_PAIR(2));
                            mvaddch(row, col, '\\');
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                    case Cell::GROUND:
                        attron(COLOR_PAIR(2));
                        mvaddch(row, col, '.');
                        attroff(COLOR_PAIR(2));
                        break;
                    case Cell::VWALL:
                        attron(COLOR_PAIR(7));
                        mvaddch(row, col, '|');
                        attroff(COLOR_PAIR(7));
                        break;
                    case Cell::HWALL:
                        attron(COLOR_PAIR(7));
                        mvaddch(row, col, '-');
                        attroff(COLOR_PAIR(7));
                        break;
                    case Cell::DOOR:
                        attron(COLOR_PAIR(8));
                        mvaddch(row, col, '+');
                        attroff(COLOR_PAIR(8));
                        break;
                    case Cell::PASSAGE:
                        attron(COLOR_PAIR(4));
                        mvaddch(row, col, '#');
                        attroff(COLOR_PAIR(4));
                        break;
                    default:
                        mvprintw(row, col, "missing CellType"); // idk dude i just put this here!
                }
            } else {
                char temp = c.occupant->charAt();
                switch (c.occupant->eType) {
                    case Entity::ENEMY:
                        attron(COLOR_PAIR(5));
                        mvaddch(row, col, temp);
                        attroff(COLOR_PAIR(5));
                        break;
                    case Entity::PLAYER:
                        attron(COLOR_PAIR(1));
                        mvaddch(row, col, temp);
                        attroff(COLOR_PAIR(1));
                        break;
                    case Entity::ITEM: {
                        if (temp == 'G') {
                            attron(COLOR_PAIR(3));
                        } else if (temp == 'P') {
                            attron(COLOR_PAIR(6));
                        } else {
                            attron(COLOR_PAIR(6));
                        }
                        mvaddch(row, col, temp);
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    default:
                        mvprintw(row, col, "missing EntityType");
                }
            }
        }
    }

    // Display UI elements
    mvprintw(LINES - 9, 0, "Race: %s", player->race.c_str());
    mvprintw(LINES - 8, 0, "Floor: %d", curFloor + 1);
    mvprintw(LINES - 7, 0, "Gold: %d", player->gold);
    mvprintw(LINES - 6, 0, "HP: %d", player->hp);
    mvprintw(LINES - 5, 0, "Atk: %d", player->atk);
    mvprintw(LINES - 4, 0, "Def: %d", player->def);
    mvprintw(LINES - 3, 0, "Action: %s", action.c_str());
    
    refresh(); // Refresh to show changes
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
        action += " (" + std::to_string(enemy->hp);
        action += " HP)";
    }
    action += "! ";
}

void View::playerMove(int dir) {
    switch (dir)
    {
    case KEY_UP:
        action += "Player moves up! ";
        break;

    case KEY_DOWN:
        action += "Player moves down! ";
        break;

    case KEY_RIGHT:
        action += "Player moves right! ";
        break;

    case KEY_LEFT:
        action += "Player moves left! ";
        break;
    
    default:
        break;
    }

    
}

void View::itemGrabbed(Item* item) {
    action += "Player picks up";
    switch(item->itemType) {
        case (Item::GOLD): {
            action += " Gold (";
            Gold* g = dynamic_cast<Gold*>(item);
            std::stringstream stream;
            stream << g->value;
            action += stream.str();
            action += ")! ";
            break;
        }
        case (Item::GOLD_HOARD): {
            action += " Gold Hoard (";
            GoldHoard* g = dynamic_cast<GoldHoard*>(item);
            std::stringstream stream;
            stream << g->value;
            action += stream.str();
            action += ")! ";
            break;
        }
        case (Item::POTION): {
            action += " Potion: ";
            Potion* p = dynamic_cast<Potion*>(item);

            action += p->stat + " ";
            if (p->value < 0) {
                action += "- ";
                action += std::to_string(0 - p->value);
            } else {
                action += "+ ";
                action += std::to_string(p->value);
            }
            action += "! ";
            break;
        }
        case (Item::COMPASS): {
            action += " Compass! Stairs to next floor visible. ";
            break;
        }
        case (Item::BARRIER_SUIT): {
            action += " Barrier Suit! Damage done to player halved. ";
            break;
        }
        default:
            break;
    }
}

void View::gameOver() {
    clear();
    mvprintw(0, 0, R"(
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
    )");
    refresh();
}

void View::gameWon(Player* p) {
    clear();
    float score = p->gold;
    if (p->race == "Human") {
        score *= 1.5;
    }
    
    mvprintw(0, 0, R"(
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
    )");
    mvprintw(LINES - 3, 0, "Score: %.2f", score);
    mvprintw(LINES - 2, 0, "...Press r to restart or q to quit");
    refresh();
}

void View::invalidActionCommand() {
    action += "Invalid command, please try again!";
}

void View::invalidCommand() {
    clear();
    mvprintw(0, 0, "Invalid command. Try again!");
    refresh();
}

void View::gameStart() {
    clear();
    mvprintw(0, 0, "Welcome to the game of CC3k!");
    mvprintw(1, 0, "Enter 'q' to quit or please enter your race: ");
    refresh();
}

void View::input() {
    mvprintw(LINES - 2, 0, "Please input command: ");
    refresh();
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
            action += "Unknown enemy";
            break;
    }
}
