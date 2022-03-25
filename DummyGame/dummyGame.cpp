#include <iostream>
#include "dummyGame.h"

DummyGame::DummyGame() {
    gameState = 0;
}

DummyGame::DummyGame(int initGameState) {
    gameState = initGameState;
}

void DummyGame::display() {
    std::cout << gameState << std::endl;
}

void DummyGame::takeInput() {}

void DummyGame::update() {
    gameState ++;
}

int DummyGame::getControlState() {
    if (gameState == 10) {
        return 0;
    }
    else {
        return 1;
    }
}