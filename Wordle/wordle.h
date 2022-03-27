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
        void Display();
        void TakeInput();
        void Update();
        int GetControlState();

    private:
        vector<string> dictionary_;
        string answer_ = "";
        unsigned remaining_attempts_;
        string SelectWord();
        string word_guessed_;
        bool IsWordValid(const string& word);
        void ToLower(string& word);
        string guess_result_;
};

#endif