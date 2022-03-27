#include "game.h"
#include "DummyGame/dummyGame.h"
#include "Wordle/wordle.h"

int main() {
    // initiate a Game object
    Game* game_ptr;
    // game_ptr = new DummyGame;
    game_ptr = new Wordle;
    while (game_ptr->GetControlState() == 1) {
        game_ptr->TakeInput();
        game_ptr->Update();
        game_ptr->Display();
    }
    return 0;
}