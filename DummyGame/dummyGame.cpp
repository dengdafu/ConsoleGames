#include <iostream>
#include "dummyGame.h"

DummyGame::DummyGame() {
    game_state_ = 0;
}

DummyGame::DummyGame(int init_game_state) {
    game_state_ = init_game_state;
}

void DummyGame::Display() {
    std::cout << game_state_ << std::endl;
}

void DummyGame::TakeInput() {}

void DummyGame::Update() {
    game_state_ ++;
}

int DummyGame::GetControlState() {
    if (game_state_ == 10) {
        return 0;
    }
    else {
        return 1;
    }
}