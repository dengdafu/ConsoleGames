#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "wordle.h"

using namespace std;

Wordle::Wordle() {
    ifstream infile("Wordle/dictionary.txt");
    for (string word; getline(infile, word);) {
        dictionary_.push_back(word);
    }
    
    answer_ = selectWord();

    remainingAttempts_ = 5;
}

void Wordle::display() {
    // TODO: Implement prorper display logic here
    cout << "answer: " <<  answer_ << endl;
    cout << "remaining attempts:" << remainingAttempts_ << endl; 
}

void Wordle::takeInput() {
    // TODO: Implement proper takeInput logic here
}

void Wordle::update() {
    // TODO: Implement proper update logic here
    // for testing
    remainingAttempts_ --;
}

int Wordle::getControlState() {
    if (remainingAttempts_ == 0) {
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