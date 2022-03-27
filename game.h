#ifndef GAME_H
#define GAME_H

class Game {
    public:
        // Display() displays the current game state to console
        virtual void Display() = 0;

        // TakeInput() takes in user inputs
        virtual void TakeInput() = 0;

        // Update() updates the game state
        virtual void Update() = 0;

        // GetControlState() returns the control state of the game.
        // 0: end
        // 1: ongoing
        // 2: pending
        virtual int GetControlState() = 0;
};

#endif