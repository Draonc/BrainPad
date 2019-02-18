//
// Created by Angela on 3/10/2017.
//

#ifndef CS311_LEX_H
#define CS311_LEX_H

#include <string>
#include <windows.h>
using namespace std;

class Lex {
public:
    void parse(string file);
    string getLine();
    void resetErrors();
    int* getErrors();
    int* getTokens();
private:
    void addChar();
    void getCharClass();
    void getNonBlank();
    int rDec();
    int lookup(char ch);
    bool isValidChar(char ch);
    int lex();
    void printErrorForLeftBracket();
    void printErrorForRightBracket();
};


#endif //CS311_LEX_H
