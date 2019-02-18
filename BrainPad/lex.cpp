#include <cstdio>
#include <iostream>
#include <fstream>
#include <stack>
#include "lex.h"

using namespace std;

// Global var
int charClass;
string lexeme = "";
char nextChar;
int nextToken;
ifstream readFile;
int index = 0;
int tokenStorage[65000];
stack<int> whileStack;
bool setFlag = false;
string outcome;
int errors[500];
int errorPos = 0;
// Token codes
enum TokenClasses {WHILE = 0, EXPR = 1, UNKNOWN = 100};
enum Tokens {ADD = 10, SUB = 11, LESS = 12, GREAT = 13,
             COMMA = 14, DOT = 15, LEFT_BRAC = 16,
             RIGHT_BRAC = 17, COMMENT = 900};

// Still need to check for: nested loops, and while used instead as a comment
/**
 * Recursive-descent parser
 * @param file path of the file to process
 */
void Lex :: parse(string file) {
    for(int i = 0; i < index; i++){
        tokenStorage[i]=0;
    }
    tokenStorage[index] = '\0';
    setFlag=false;
    index = 0;
    while(!whileStack.empty()){
        whileStack.pop();
    }
    readFile.open(file, ios::in);
    int temp = 0;
    if (readFile.is_open()) {
        if(((temp = rDec()) == 2000) && !setFlag){
            outcome = "";
        }else if(setFlag || temp == -2){
            printErrorForLeftBracket();
            outcome = "Syntax Error: Missing bracket";
        }else{
            outcome = "Unknown Error";
        }
    }
    else {
        cout << "ERROR: cannot open file \n" << endl;
    }
    //for(int i = 0; i < index-1; i++){
    //    cout << tokenStorage[i] << endl;
    //}
    readFile.close();
}

void Lex :: printErrorForLeftBracket(){
    while(!whileStack.empty()){
        cout << "Left Bracket Error at: " << whileStack.top() << endl;
        errors[errorPos] = whileStack.top();
        errorPos++;
        whileStack.pop();
    }
}

void Lex :: printErrorForRightBracket(){
    cout << "Right Bracket Error at: " << index << endl;
    errors[errorPos] = index;
    errorPos++;
}
int Lex :: rDec(){
    nextToken = lex();
    if(nextToken == LEFT_BRAC){
        whileStack.push(index);
        return rDec();
    }else if(nextToken == RIGHT_BRAC){
        if(!whileStack.empty()){
            whileStack.pop();
        }else{
            printErrorForRightBracket();
            setFlag = true;
        }
        return rDec();
    }else if(!readFile.eof()){
        return rDec();
    }else if(readFile.eof()){
        if(whileStack.empty()){
            return 2000;
        }else if(whileStack.size() > 0){
            return -2;
        }else{
            return -3;
        }
    }else{
        return rDec();
    }
}
/**
 * Adds a character to the lexeme string
 */
void Lex :: addChar() {
    lexeme.push_back(nextChar);
}

/**
 * If the character isValid, assign a charClass
 */
void Lex :: getCharClass() {
    if (isValidChar(nextChar)) {
        if ((nextToken == LEFT_BRAC) || (nextToken == RIGHT_BRAC)) {
            charClass = WHILE;
        }
        else {
            charClass = EXPR;
        }
    }
    else {
        charClass = UNKNOWN;
    }
}

/**
 * Get the next NonBlank character and check its class
 */
void Lex :: getNonBlank() {
    do {
        nextChar = (char) readFile.get();
        index++;
    }
    while(isspace(nextChar) && (nextChar != EOF));
    getCharClass();
}

/**
 * Assigns the nextToken code for the appropriate BrainFuck character. No code if !isValidChar.
 * @param ch nextChar
 * @return nextToken code
 */
int Lex :: lookup(char ch) {
    switch(ch) {
        case '+':
            addChar();
            nextToken = ADD;
            break;
        case '-':
            addChar();
            nextToken = SUB;
            break;
        case '<':
            addChar();
            nextToken = LESS;
            break;
        case '>':
            addChar();
            nextToken = GREAT;
            break;
        case ',':
            addChar();
            nextToken = COMMA;
            break;
        case '.':
            addChar();
            nextToken = DOT;
            break;
        case '[':
            addChar();
            nextToken = LEFT_BRAC;
            break;
        case ']':
            addChar();
            nextToken = RIGHT_BRAC;
            break;
        default:
            nextToken = COMMENT;
            break;
    }
    return nextToken;
}

/**
 * Determines if the character isValidChar in BrainFuck.
 * @param ch nextChar
 * @return if the character isValid
 */
bool Lex :: isValidChar(char ch) {
    bool isValid;
    switch (ch) {
        case '+':
            isValid = true;
            break;
        case '-':
            isValid = true;
            break;
        case '<':
            isValid = true;
            break;
        case '>':
            isValid = true;
            break;
        case ',':
            isValid = true;
            break;
        case '.':
            isValid = true;
            break;
        case '[':
            isValid = true;
            break;
        case ']':
            isValid = true;
            break;
        default:
            isValid = false;
            break;
    }
    return isValid;
}

/**
 * Lexical analyzer
 * @return nextToken code
 */
int Lex :: lex() {
    lexeme = "";
    getNonBlank();
    switch(charClass) {
        case WHILE:
            lookup(nextChar);
            getCharClass();

            break;
        case EXPR:
            lookup(nextChar);
            getCharClass();

            break;
        case UNKNOWN:
            lookup(nextChar);
            getCharClass();

            break;
        default:
            break;
    }
    tokenStorage[index] = nextToken;
    return nextToken;
}


string Lex :: getLine() {
    return outcome;
}


void Lex ::resetErrors(){
    for(int i = 0; i < 500; i++){
        errors[i] = -1;
    }
}

int* Lex ::getErrors(){
    return errors;
}

int* Lex ::getTokens(){
    for(int i = 0; i < index; i++){
        if((tokenStorage[i] == 0) || (tokenStorage[i] == 900)){
            int temp1 = i;
            for(int j = i+1; j < index+1; j++, temp1++){
                tokenStorage[temp1] = tokenStorage[j];
            }
            index--;
            i--;
        }
    }
    int end;
    for(int loc = 1; loc < index; loc++){
        if((tokenStorage[loc-1] == 16) && (tokenStorage[loc] == 17) && tokenStorage[loc+1] != '\0'){
            int temp1 = loc-1;
            while(tokenStorage[temp1] != '\0'){
                tokenStorage[temp1] = tokenStorage[temp1+2];
                tokenStorage[temp1+1] = tokenStorage[temp1+3];
                temp1+=2;
            }
            index-=2;
        }
        end = loc;
        cout << tokenStorage[loc] << endl;
    }
    tokenStorage[end+1] = '\0';
    return tokenStorage;
}
