#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <map>
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
        const map<char, int> kDirectionMap = {{'w', -1}, {'s', 1}, {'a', -2}, {'d', 2}};
        struct GameState {
            pair<int, int> head;
            list<pair<int, int>> body;
            pair<int, int> food;
            int score;
            int direction;
            int special_food_countdown;
            int pace;
        };
        int control_state_;
        GameState game_state_;

        void InitializeCanvas();
        void InitializeGameState();
        void GenerateHead();
        void GenerateFood();
        // if changing direction is successful return true, else false.
        bool ChangeDirection(char dir);
        // if eat food return true, else false.
        bool SnakeMove();
        void UpdateScore();
        void UpdatePace();
        void ChangeToOngoingState();
        void ChangeToPausedState();
        void ChangeToOverState();
};

#endif