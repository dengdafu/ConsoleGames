#include "game.h"
#include "DummyGame/dummyGame.h"
#include "Wordle/wordle.h"

int main() {
    // initiate a Game object
    Game* gamePtr;
    // gamePtr = new DummyGame;
    gamePtr = new Wordle;
    while (gamePtr->getControlState()) {
        gamePtr->display();
        gamePtr->update();
    }
    return 0;
}