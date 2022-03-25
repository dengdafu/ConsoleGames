#include "game.h"
#include "DummyGame/dummyGame.h"

int main() {
    // initiate a Game object
    Game* gamePtr; 
    gamePtr = new DummyGame;
    while (gamePtr->getControlState()) {
        gamePtr->display();
        gamePtr->update();
    }
    return 0;
}