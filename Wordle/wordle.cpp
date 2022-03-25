#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "wordle.h"
#include "../utils/utils.h"

using namespace std;
using namespace utils;

Wordle::Wordle() {
    ifstream infile("Wordle/dictionary.txt");
    for (string word; getline(infile, word);) {
        dictionary_.push_back(word);
    }
    
    answer_ = selectWord();

    cout << answer_ << endl;

    remainingAttempts_ = maxAttempts;

    // g: green
    // y: yellow
    // b: black
    guessResult = "yyyyy";

    cout << "Wordle started." << endl;
}

void Wordle::display() {
    if (guessResult == "ggggg") {
        cout << "The word is indeed " << answer_ << endl;
        cout << "Attempts used: " << maxAttempts - remainingAttempts_ << endl;
    }
    else if (remainingAttempts_ == 0) {
        cout << "All attempts failed." << endl;
    }
    else {
        cout << "Your guess received result: " << guessResult << endl;
        cout << "Remaining attempts: " << remainingAttempts_ << endl;
    }
}

void Wordle::takeInput() {
    cout << "Enter a word here: ";
    string wordEntered;
    cin >> wordEntered;
    while (!isWordValid(wordEntered)) {
        wordEntered.clear();
        cout << "Invalid word entered, please re-enter: ";
        cin >> wordEntered;
    }

    toLower(wordEntered);
    wordGuessed_ = wordEntered;
}

void Wordle::update() {
    guessResult = "yyyyy";
    map<char, int> counter = charCount(answer_);
    for (unsigned i = 0; i < wordLength; i++) {
        if (wordGuessed_[i] == answer_[i]) {
            guessResult[i] = 'g';
            counter[i] -=  1;
            continue;
        }
        if (counter.find(wordGuessed_[i]) == counter.end()) {
            guessResult[i] = 'b';
        }
    }
    for (unsigned i = 0; i < wordLength; i++) {
        if (guessResult[i] == 'y' && counter[wordGuessed_[i]] == 0 ) {
            guessResult[i] = 'b';
        }
    }

    remainingAttempts_--;
}

int Wordle::getControlState() {
    if (remainingAttempts_ == 0 || guessResult == "ggggg") {
        return 0;
    }
    else {
        return 1;
    }
}

string Wordle::selectWord() {
    // refactor error handling here
    if (dictionary_.size() == 0) {
        return "";
    }
    srand(time(NULL));
    return dictionary_[rand() % dictionary_.size()];
}

void Wordle::toLower(string& word) {
    transform(
        word.begin(),
        word.end(),
        word.begin(),
        [](unsigned char c){ return std::tolower(c); });
}

bool Wordle::isWordValid(const string& word) {
    // check length
    if (word.size() != wordLength) {
        return false;
    }

    // check if all letters
    for(const char& c : word) {
        if (!isalpha(c)) {
            return false;
        }
    }

    return true;
}