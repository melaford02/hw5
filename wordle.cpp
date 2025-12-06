//pasted from vscode for running tests

#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#endif
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// helper function
void generateWords(string& word, int pos, const string& pattern, string remaining, const set<string>& dict, set<string>& results);

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> results;
    if(in.empty()) return results;
    
    string word = in;
    generateWords(word, 0, in, floating, dict, results);
    return results;
}

void generateWords(string& word, int pos, const string& pattern, string remaining, const set<string>& dict, set<string>& results){
    // if we filled the whole word
    if(pos == (int)pattern.size()) {
        // make sure we used all the floating letters
        if(remaining.empty() && dict.find(word) != dict.end()) {
            results.insert(word);
        }
        return;
    }
    
    // skip positions that already have letters
    if(pattern[pos] != '-') {
        generateWords(word, pos + 1, pattern, remaining, dict, results);
        return;
    }
    
    // count how many blank spots are left
    int blanksLeft = 0;
    for(int i = pos; i < (int)pattern.size(); i++) {
        if(pattern[i] == '-') {
            blanksLeft++;
        }
    }
    
    // if we don't have enough blanks for the floating letters, stop
    if(blanksLeft < (int)remaining.size()) {
        return;
    }
    
    if(blanksLeft == (int)remaining.size()) {
        // try each floating letter at this position
        for(int i = 0; i < (int)remaining.size(); i++) {
          word[pos] = remaining[i];
          string left = remaining.substr(0,i);
          string right = remaining.substr(i + 1);
          string newRemaining = left + right;
          generateWords(word, pos + 1, pattern, newRemaining, dict, results);
        }
    } else {
        
        for(int i = 0; i < (int)remaining.size(); i++) {
            word[pos] = remaining[i];
            string newRemaining = remaining.substr(0, i) + remaining.substr(i + 1);
            generateWords(word, pos + 1, pattern, newRemaining, dict, results);
        }
        
        // then try all letters (but skip duplicates)
        for(char c = 'a'; c <= 'z'; c++) {
            // check if this letter is in remaining 
            bool inRemaining = false;
            for(int i = 0; i < (int)remaining.size(); i++) {
                if(remaining[i] == c) {
                    inRemaining = true;
                    break;
                }
            }
            
            if(!inRemaining) {
                word[pos] = c;
                generateWords(word, pos + 1, pattern, remaining, dict, results);
            }
        }
    }
    
    word[pos] = '-';
}