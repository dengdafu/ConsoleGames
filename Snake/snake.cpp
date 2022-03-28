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
// Message line 1                                                        Score: 9999  19x82
constexpr int kHeight = 19;
constexpr int kWidth = 82;
constexpr int kUpperBound = 0;
constexpr int kLowerBound = 16;
constexpr int kLeftBound = 0;
constexpr int kRightBound = 81;
constexpr int kInitPace = 120;
constexpr int kFastestPace = 40;
constexpr const char* kBoundaryRow = "**********************************************************************************";
constexpr const char* kRegularRow = "*                                                                                *";
constexpr const char* kEmptyRow = "                                                                                  ";
constexpr const char* kPausedMsg = "Press 'wasd' to start, 'r' to regenerate, 'q' to quit.                ";
constexpr const char* kOngoingMsg = "Press 'p' to pause, 'q' to quit.                                      ";
constexpr const char* kOverMsg = "Game over, press 'r' to restart, 'q' to quit.                         ";

#include <string>
#include <iostream>
#include <algorithm>
#include <curses.h>
#include "snake.h"

using namespace std;

Snake::Snake() {
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(false);
    resizeterm(kHeight, kWidth);
    InitializeCanvas();
    InitializeGameState();
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
            if (control_state_ == kPaused || control_state_ == kOver) {
                InitializeCanvas();
                InitializeGameState();
            }
            break;
        case 'p':
            ChangeToPausedState();
            break;
        case 'w': case 'a': case 's': case 'd':
            if(ChangeDirection(input)){
                ChangeToOngoingState();
            }
            break;
        default:
            break;
    }
}

void Snake::Update() {
    if (control_state_ == kOngoing) {
        if(SnakeMove()){
            GenerateFood();
            UpdateScore();
            UpdatePace();
        }
    }
}

int Snake::GetControlState() {
    return control_state_;
}

void Snake::InitializeGameState() {
    control_state_ = kPaused;
    game_state_.direction = 0;
    game_state_.body.clear();
    game_state_.special_food_countdown = 5;
    game_state_.pace = kInitPace;
    timeout(game_state_.pace);
    game_state_.score = 0;
    mvprintw(kLowerBound + 2, kWidth - 5, to_string(game_state_.score).c_str());
    GenerateHead();
    GenerateFood();
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
    mvprintw(kLowerBound + 2, 0, kPausedMsg);

    // display initial score
    mvprintw(kLowerBound + 2, kWidth - 12, "SCORE: ");
}

void Snake::GenerateHead() {
    game_state_.head.first = 1 + rand() % (kLowerBound - kUpperBound - 1);
    game_state_.head.second = 1 + rand() % (kRightBound - kLeftBound - 1);
    mvaddch(game_state_.head.first, game_state_.head.second, '@');
}

void Snake::GenerateFood() {
    game_state_.food.first = 1 + rand() % (kLowerBound - kUpperBound - 1);
    game_state_.food.second = 1 + rand() % (kRightBound - kLeftBound - 1);
    while (game_state_.food == game_state_.head) {
        game_state_.food.first = 1 + rand() % (kLowerBound - kUpperBound - 1);
        game_state_.food.second = 1 + rand() % (kRightBound - kLeftBound - 1);
    }
    if (game_state_.special_food_countdown == 0) { // special food every once in a while
        mvaddch(game_state_.food.first, game_state_.food.second, '$');
        game_state_.special_food_countdown = 5;
    }
    else {
        mvaddch(game_state_.food.first, game_state_.food.second, '#');
        game_state_.special_food_countdown --;
    }
}

bool Snake::ChangeDirection(char dir) {
    int num_dir = kDirectionMap.at(dir);
    if (game_state_.direction == 0 || game_state_.direction != -num_dir) {
        game_state_.direction = num_dir;
        return true;
    }
    return false;
}

bool Snake::SnakeMove() {
    pair<int, int> new_head_posn = game_state_.head;
    if (game_state_.direction == kDirectionMap.at('w')) {
        new_head_posn.first--;
        mvaddch(new_head_posn.first, new_head_posn.second, '^');
    }
    else if (game_state_.direction == kDirectionMap.at('s')) {
        new_head_posn.first++;
        mvaddch(new_head_posn.first, new_head_posn.second, 'v');
    }
    else if (game_state_.direction == kDirectionMap.at('a')) {
        new_head_posn.second--;
        mvaddch(new_head_posn.first, new_head_posn.second, '<');
    }
    else {
        new_head_posn.second++;
        mvaddch(new_head_posn.first, new_head_posn.second, '>');
    }

    // Game over
    if (new_head_posn.first == kUpperBound ||
        new_head_posn.first == kLowerBound ||
        new_head_posn.second == kLeftBound ||
        new_head_posn.second == kRightBound ||
        find(game_state_.body.begin(), game_state_.body.end(), new_head_posn) != game_state_.body.end()) {
        mvaddch(game_state_.head.first, game_state_.head.second, 'X');
        mvaddch(new_head_posn.first, new_head_posn.second, '*');
        ChangeToOverState();
        return false;
    }

    game_state_.body.push_front(game_state_.head);
    mvaddch(game_state_.head.first, game_state_.head.second, 'o');
    game_state_.head = new_head_posn;
    // Eat food
    if (new_head_posn == game_state_.food) {
        return true;    
    }
    pair<int, int>& tail = game_state_.body.back();
    game_state_.body.pop_back();
    mvaddch(tail.first, tail.second, ' ');
    return false;
}

void Snake::UpdateScore() {
    game_state_.score += (game_state_.special_food_countdown == 4)? 50: 10;
    mvprintw(kLowerBound + 2, kWidth - 5, to_string(game_state_.score).c_str());
}

void Snake::UpdatePace() {
    if (game_state_.pace > kFastestPace) {
        game_state_.pace -= 2;
        timeout(game_state_.pace);        
    }
}

void Snake::ChangeToOngoingState() {
    if (control_state_ == kPaused) {
        control_state_ = kOngoing;
        mvprintw(kLowerBound + 2, 0, kOngoingMsg);
    }
}

void Snake::ChangeToPausedState() {
    if (control_state_ == kOngoing) {
        control_state_ = kPaused;
        mvprintw(kLowerBound + 2, 0, kPausedMsg);
    }
}

void Snake::ChangeToOverState() {
    control_state_ = kOver;
    mvprintw(kLowerBound + 2, 0, kOverMsg);
}