#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <ncurses.h>
#include "../game.h"

using namespace std;

class Snake: public Game {
    public:
        Snake();
        ~Snake();
        void Display();
        void TakeInput();
        void Update();
        int GetControlState();
    private:
        struct GameState {
            pair<int, int> head;
            list<pair<int, int>> body;
            pair<int, int> food;
            int score;
        };
        WINDOW* canvas_ptr;
        int control_state_;
        GameState game_state_;
        bool is_cursor_hideable_;

        void InitializeCanvas();
        void InitializeGameState();

        void GenerateHead();
        void GenerateFood();
};

#endif