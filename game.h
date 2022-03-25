#ifndef GAME_H
#define GAME_H

class Game {
    public:
        // display() displays the current game state to console
        virtual void display() = 0;

        // takeInput() takes in user inputs
        virtual void takeInput() = 0;

        // update() updates the game state
        virtual void update() = 0;

        // getControlState() returns the control state of the game.
        // 0: end
        // 1: ongoing
        // 2: pending
        virtual int getControlState() = 0;
};

#endif