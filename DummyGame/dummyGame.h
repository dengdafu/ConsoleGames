#ifndef DUMMY_GAME_H
#define DUMMY_GAME_H

#include "../game.h"

class DummyGame: public Game {
    public:
        DummyGame();
        DummyGame(int initGameState);
        void display();
        void takeInput();
        void update();
        int getControlState();
    private:
        int gameState;
};

#endif