#ifndef DUMMY_GAME_H
#define DUMMY_GAME_H

#include "../game.h"

class DummyGame: public Game {
    public:
        DummyGame();
        DummyGame(int init_game_state);
        void Display();
        void TakeInput();
        void Update();
        int GetControlState();
    private:
        int game_state_;
};

#endif