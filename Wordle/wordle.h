#ifndef WORDLE_H
#define WORLDE_H

#include <vector>
#include <string>
#include "../game.h"

using namespace std;

class Wordle : public Game {
    public:
        Wordle();
        void display();
        void takeInput();
        void update();
        int getControlState();

    private:
        vector<string> dictionary_;
        string answer_ = "";
        int remainingAttempts_;
        string selectWord();
};

#endif