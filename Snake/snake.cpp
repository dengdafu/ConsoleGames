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
constexpr const char* kBoundaryRow = "**********************************************************************************";
constexpr const char* kRegularRow = "*                                                                                *";
constexpr const char* kEmptyRow = "                                                                                  ";

#include <string>
#include <iostream>
#include "snake.h"
#include <curses.h>
#include <utility>

using namespace std;

Snake::Snake() {
    srand(time(NULL));
    initscr();
    timeout(100);
    resizeterm(kHeight, kWidth); 
    // Some terminals do not support hiding cursor, thus the following workaround
    is_cursor_hideable_ = !(curs_set(0) == ERR);
    InitializeGameState();
    InitializeCanvas();
    control_state_ = kPaused;
}

Snake::~Snake() {
    endwin();
}

void Snake::Display() {
    // move(kMainWinHeight-1, 0);
    if (!is_cursor_hideable_) {
        mvaddch(kHeight-3, 0, ' ');
        move(kHeight-3, 0);
    }
    refresh();
}

void Snake::TakeInput() {
    switch(getch()){
        case 'q':
            control_state_ = kEnd;
            break;
        case 'r':
            if (control_state_ == kPaused) {
                InitializeGameState();
                InitializeCanvas();
            }
            break;
        default:
            break;
    }
}

void Snake::Update() {

}

int Snake::GetControlState() {
    return control_state_;
}

void Snake::InitializeGameState() {
    GenerateHead();
    GenerateFood();
    game_state_.score = 0;
}


void Snake::InitializeCanvas() {
    // draw all rows
    mvprintw(0, 0, kBoundaryRow);
    for (int i = 1; i < kHeight - 4; i++) {
        mvprintw(i, 0, kRegularRow);
    }
    mvprintw(kHeight - 4, 0, kBoundaryRow);
    for (int i = kHeight - 3; i < kHeight; i++) {
        mvprintw(i, 0, kEmptyRow);
    }
    
    // display initial message
    mvprintw(kHeight - 2, 0, "Press 'wasd' to start.");
    mvprintw(kHeight - 1, 0, "Press 'r' to regenerate.");

    // display initial score
    mvprintw(kHeight - 2, kWidth - 12, "SCORE: ");
    mvprintw(kHeight - 2, kWidth - 5, to_string(game_state_.score).c_str());

    // display head and food
    mvaddch(game_state_.head.first, game_state_.head.second, '@');
    mvaddch(game_state_.food.first, game_state_.food.second, '$');
}

void Snake::GenerateHead() {
    game_state_.head.first = 1 + rand() % (kHeight - 5);
    game_state_.head.second = 1 + rand() % (kWidth - 2);
}

void Snake::GenerateFood() {
    game_state_.food.first = 1 + rand() % (kHeight - 5);
    game_state_.food.second = 1 + rand() % (kWidth - 2);
    while (game_state_.food == game_state_.head) {
        game_state_.food.first = 1 + rand() % (kHeight - 5);
        game_state_.food.second = 1 + rand() % (kWidth - 2);
    }    
}