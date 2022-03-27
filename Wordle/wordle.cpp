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

constexpr unsigned kMaxAttempts = 6;
constexpr unsigned kWordLength = 5;

Wordle::Wordle() {
    ifstream infile("Wordle/dictionary.txt");
    for (string word; getline(infile, word);) {
        dictionary_.push_back(word);
    }
    
    answer_ = SelectWord();

    cout << answer_ << endl;

    remaining_attempts_ = kMaxAttempts;

    // g: green
    // y: yellow
    // b: black
    guess_result_ = "yyyyy";

    cout << "Wordle started." << endl;
}

void Wordle::Display() {
    if (guess_result_ == "ggggg") {
        cout << "The word is indeed " << answer_ << endl;
        cout << "Attempts used: " << kMaxAttempts - remaining_attempts_ << endl;
    }
    else if (remaining_attempts_ == 0) {
        cout << "All attempts failed." << endl;
    }
    else {
        cout << "Your guess received result: " << guess_result_ << endl;
        cout << "Remaining attempts: " << remaining_attempts_ << endl;
    }
}

void Wordle::TakeInput() {
    cout << "Enter a word here: ";
    string word_entered;
    cin >> word_entered;
    while (!IsWordValid(word_entered)) {
        word_entered.clear();
        cout << "Invalid word entered, please re-enter: ";
        cin >> word_entered;
    }

    ToLower(word_entered);
    word_guessed_ = word_entered;
}

void Wordle::Update() {
    guess_result_ = "yyyyy";
    map<char, int> counter = CharCount(answer_);
    for (unsigned i = 0; i < kWordLength; i++) {
        if (word_guessed_[i] == answer_[i]) {
            guess_result_[i] = 'g';
            counter[i] -=  1;
            continue;
        }
        if (counter.find(word_guessed_[i]) == counter.end()) {
            guess_result_[i] = 'b';
        }
    }
    for (unsigned i = 0; i < kWordLength; i++) {
        if (guess_result_[i] == 'y' && counter[word_guessed_[i]] == 0 ) {
            guess_result_[i] = 'b';
        }
    }

    remaining_attempts_--;
}

int Wordle::GetControlState() {
    if (remaining_attempts_ == 0 || guess_result_ == "ggggg") {
        return 0;
    }
    else {
        return 1;
    }
}

string Wordle::SelectWord() {
    // refactor error handling here
    if (dictionary_.size() == 0) {
        return "";
    }
    srand(time(NULL));
    return dictionary_[rand() % dictionary_.size()];
}

void Wordle::ToLower(string& word) {
    transform(
        word.begin(),
        word.end(),
        word.begin(),
        [](unsigned char c){ return std::tolower(c); });
}

bool Wordle::IsWordValid(const string& word) {
    // check length
    if (word.size() != kWordLength) {
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