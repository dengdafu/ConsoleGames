#include "game.h"
#include "DummyGame/dummyGame.h"
#include "Wordle/wordle.h"
#include "Snake/snake.h"

int main() {
    // initiate a Game object
    Game* game_ptr;
    // game_ptr = new DummyGame;
    // game_ptr = new Wordle;
    game_ptr = new Snake;
    while (game_ptr->GetControlState() != 0) {
        game_ptr->TakeInput();
        game_ptr->Update();
        game_ptr->Display();
    }
    delete game_ptr;
    return 0;
}