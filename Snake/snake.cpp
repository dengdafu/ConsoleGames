// **********************************************************************************
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                                *
// *                                                                          15x80 *
// ********************************************************************************** 17x82
// 
// Message line 1                                                        Score: 9999
// Message line 2                                                                     20x82
constexpr int kHeight = 20;
constexpr int kWidth = 82;
constexpr int kUpperBound = 0;
constexpr int kLowerBound = 16;
constexpr int kLeftBound = 0;
constexpr int kRightBound = 81;
constexpr const char* kBoundaryRow = "**********************************************************************************";
constexpr const char* kRegularRow = "*                                                                                *";
constexpr const char* kEmptyRow = "                                                                                  ";

#include <string>
#include <iostream>
#include <utility>
#include <curses.h>
#include "snake.h"

using namespace std;

Snake::Snake() {
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(false);
    timeout(100);
    resizeterm(kHeight, kWidth);
    InitializeGameState();
    InitializeCanvas();
    control_state_ = kPaused;    
}

Snake::~Snake() {
    endwin();
}

void Snake::Display() {
    refresh();
}

void Snake::TakeInput() {
    char input = getch();
    switch(input) {
        case 'q':
            control_state_ = kEnd;
            break;
        case 'r':
            if (control_state_ == kPaused) {
                InitializeGameState();
                InitializeCanvas();
            }
            break;
        case 'w': case 'a': case 's': case 'd':
            ChangeDirection(input);
            break;
        default:
            break;
    }
}

void Snake::Update() {
    if (control_state_ == kOngoing) {
        SnakeMove();
    }
}

int Snake::GetControlState() {
    return control_state_;
}

void Snake::InitializeGameState() {
    GenerateHead();
    GenerateFood();
    game_state_.score = 0;
    game_state_.direction = kDirectionMap.at('w');
}


void Snake::InitializeCanvas() {
    // draw all rows
    mvprintw(kUpperBound, 0, kBoundaryRow);
    for (int i = 1; i < kLowerBound; i++) {
        mvprintw(i, 0, kRegularRow);
    }
    mvprintw(kLowerBound, 0, kBoundaryRow);
    for (int i = kLowerBound + 1; i < kHeight; i++) {
        mvprintw(i, 0, kEmptyRow);
    }
    
    // display initial message
    mvprintw(kLowerBound + 2, 0, "Press 'wasd' to start.");
    mvprintw(kLowerBound + 3, 0, "Press 'r' to regenerate.");

    // display initial score
    mvprintw(kLowerBound + 2, kWidth - 12, "SCORE: ");
    mvprintw(kLowerBound + 2, kWidth - 5, to_string(game_state_.score).c_str());

    // display head and food
    mvaddch(game_state_.head.first, game_state_.head.second, '@');
    mvaddch(game_state_.food.first, game_state_.food.second, '$');
}

void Snake::GenerateHead() {
    game_state_.head.first = 1 + rand() % (kLowerBound - kUpperBound - 1);
    game_state_.head.second = 1 + rand() % (kRightBound - kLeftBound - 1);
}

void Snake::GenerateFood() {
    game_state_.food.first = 1 + rand() % (kLowerBound - kUpperBound - 1);
    game_state_.food.second = 1 + rand() % (kRightBound - kLeftBound - 1);
    while (game_state_.food == game_state_.head) {
        game_state_.food.first = 1 + rand() % (kLowerBound - kUpperBound - 1);
        game_state_.food.second = 1 + rand() % (kRightBound - kLeftBound - 1);
    }    
}

void Snake::ChangeDirection(char dir) {
    int num_dir = kDirectionMap.at(dir);
    if (control_state_ == kPaused) {
        control_state_ = kOngoing;
        game_state_.direction = num_dir;
    }
    else if (game_state_.direction != -num_dir) {
        game_state_.direction = num_dir;
    }
}

void Snake::SnakeMove() {
    // TODO: add body movement logic
    if (game_state_.direction == kDirectionMap.at('w')) {
        if (game_state_.head.first == kUpperBound + 1) {
            mvaddch(game_state_.head.first, game_state_.head.second, '@');
            control_state_ = kEnd;
            return;
        }
        mvaddch(game_state_.head.first--, game_state_.head.second, ' ');
        mvaddch(game_state_.head.first, game_state_.head.second, '^');
    }
    else if (game_state_.direction == kDirectionMap.at('s')) {
        if (game_state_.head.first == kLowerBound - 1) {
            mvaddch(game_state_.head.first, game_state_.head.second, '@');
            control_state_ = kEnd;
            return;
        }
        mvaddch(game_state_.head.first++, game_state_.head.second, ' ');
        mvaddch(game_state_.head.first, game_state_.head.second, 'v');
    }
    else if (game_state_.direction == kDirectionMap.at('a')) {
        if (game_state_.head.second == kLeftBound + 1) {
            mvaddch(game_state_.head.first, game_state_.head.second, '@');
            control_state_ = kEnd;
            return;
        }
        mvaddch(game_state_.head.first, game_state_.head.second--, ' ');
        mvaddch(game_state_.head.first, game_state_.head.second, '<');
    }
    else {
        if (game_state_.head.second == kRightBound - 1) {
            mvaddch(game_state_.head.first, game_state_.head.second, '@');
            control_state_ = kEnd;
            return;
        }
        mvaddch(game_state_.head.first, game_state_.head.second++, ' ');
        mvaddch(game_state_.head.first, game_state_.head.second, '>');
    }
}