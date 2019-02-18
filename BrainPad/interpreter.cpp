#include <cstdio>
#include <iostream>
#include <fstream>
#include <stack>

#include "interpreter.h"
#include "mainwindow.h"


char data[30000];
char *d;
const char *p;
//MainWindow window;
Interpreter::Interpreter()
{
}

void Interpreter::setData(const char prog[]){
    d=data;
    p=prog;

    for(int i = 0; i<5 ; i++){
        cout << p[i];
    }
}

void Interpreter::pointerInc(){
    d++;
}

void Interpreter::pointerDec(){
    d--;
}

void Interpreter::bitInc(){
    (*d)++;
}

void Interpreter::bitDec(){
    (*d)--;
}

void Interpreter::output(){
 // MainWindow window;
  //window.output(*d);
}

void Interpreter::input(){
   // cin>>*d;
}

void Interpreter::bracketOpen(){
    int bal = 1;
    if(*d == '\0'){
        do{
            p++;
            if(*p == '[')
                bal++;
            else if(*p == ']')
                bal--;
        }while(bal !=0);
    }
}

void Interpreter::bracketClose(){
    int bal = 0;
        do{
            if(*p == '[')
                bal++;
            else if(*p == ']')
                bal--;
            p--;
        }while(bal !=0);
}

void Interpreter::evaluate(){
    while(*p){
        switch(*p){
        case '>':
          pointerInc();
          break;
        case '<':
          pointerDec();
          break;
        case '+':
          bitInc();
          break;
        case '-':
          bitDec();
          break;
        case '.':
          output();
          break;
        case ',':
          input();
          break;
        case '[':
          bracketOpen();
          break;
        case ']':
          bracketClose();
          break;
          }
         p++;
        }
    }
