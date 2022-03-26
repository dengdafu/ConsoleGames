#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>
#include "../game.h"

class Snake: public Game {
    public:
        Snake();
        ~Snake();
        void Display();
        void TakeInput();
        void Update();
        int GetControlState();
    private:
        WINDOW* main_win_ptr_;
        WINDOW* info_win_ptr_;
        int control_state_;
        void InitializeWindows();
};

#endif