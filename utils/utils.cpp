#include "utils.h"

using namespace std;

map<char, int> utils::CharCount(const string &s) {
    map<char, int> counter;
    for(const char& c : s) {
        if (counter.find(c) != counter.end()) {
            counter[c]++;
        }
        else {
            counter[c] = 1;
        }
    }
    return counter;
}