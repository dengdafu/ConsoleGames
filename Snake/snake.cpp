#include <string>
#include <iostream>
#include "snake.h"
#include <curses.h>

using namespace std;

constexpr int kWinWidth = 102;
constexpr int kMainWinHeight = 22;
constexpr int kInfoWinHeight = 5;


Snake::Snake() {
    main_win_ptr_ = initscr();
    wresize(main_win_ptr_, kMainWinHeight, kWinWidth);
    info_win_ptr_ = newwin(kInfoWinHeight, kWinWidth, kMainWinHeight, 0);
    InitializeWindows();
    control_state_ = PAUSED;
}

void Snake::InitializeWindows() {
    // draw boundaries
    char horizontal_boundary[kWinWidth];
    fill(begin(horizontal_boundary), end(horizontal_boundary), '*');
    mvwprintw(main_win_ptr_, 0, 0, horizontal_boundary);
    for (int i = 1; i < kMainWinHeight - 1; i++) {
        mvwaddch(main_win_ptr_, i, 0, '*');
        mvwaddch(main_win_ptr_, i, kWinWidth - 1, '*');
    }
    mvwprintw(main_win_ptr_, kMainWinHeight - 1, 0, horizontal_boundary);
    wrefresh(main_win_ptr_);

    // display initial message
    mvwprintw(info_win_ptr_, 1, 0, "Press 's' to start new game.");
    wrefresh(info_win_ptr_);
}

Snake::~Snake() {
    endwin();
}

void Snake::Display() {
}

void Snake::TakeInput() {
    switch(getch()){
        case 'q':
            control_state_ = END;
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