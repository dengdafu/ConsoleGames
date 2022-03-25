#ifndef WORDLE_H
#define WORLDE_H

/*
Wordle game implemented as described in https://en.wikipedia.org/wiki/Wordle
*/

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
        unsigned remainingAttempts_;
        string selectWord();
        const unsigned maxAttempts = 6;
        const unsigned wordLength = 5;
        string wordGuessed_;
        bool isWordValid(const string& word);
        void toLower(string& word);
        string guessResult;
};

#endif