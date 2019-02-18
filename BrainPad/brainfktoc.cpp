#include <cstdio>
#include <iostream>
#include <fstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "consoledialog.h"
#include "syntaxhighlighter.h"
#include "lex.h"
#include "brainfktoc.h"

int whileCounter = 0;
QFile BrainFkToCFile("BrainFile.c");

void Brain ::convertToC(int *errors, int *tokenStorage){
    if(errors[0] == -1){
        if(BrainFkToCFile.open(QFile::WriteOnly | QFile::Text)){
            BrainFkToCFile.write("#include <stdlib.h>\n");
            BrainFkToCFile.write("#include <stdio.h>\n");
            BrainFkToCFile.write("#include <string.h>\n");
            BrainFkToCFile.write("#include <errno.h>\n");
            BrainFkToCFile.write("int main(int argc, char *argv[]){\n");
            BrainFkToCFile.write("  unsigned char list[4096];\n");
            BrainFkToCFile.write("  int tempBuffer = 0;\n");
            BrainFkToCFile.write("  int index = 0;\n");
            int i = 0;

            while((tokenStorage[i] != '\0')|| i == 65000){
                switch(tokenStorage[i]){
                case 10:addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  list[index]++;\n");
                    break;
                case 11:addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  list[index]--;\n");
                    break;
                case 12:addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  if(index == 0){\n");
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("    index = 4096;\n");
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  }else{\n");
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("    index--;\n");
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  }\n");
                    break;
                case 13:addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  if(index == 4096){\n");
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("    index = 0;\n");
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  }else{\n");
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("    index++;\n");
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  }\n");
                    break;
                case 14:addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  tempBuffer = fgetc(stdin);\n");
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  list[index] = tempBuffer;\n");

                    break;
                case 15:addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  printf(\"%c\", list[index]);\n");
                    break;
                case 16:addWhiteSpaceIfNec();
                        whileCounter++;
                        BrainFkToCFile.write("  while(list[index] != 0){\n");
                    break;
                case 17:whileCounter--;
                        addWhiteSpaceIfNec();
                        BrainFkToCFile.write("  }\n");
                    break;
                }

                i++;
            }

            BrainFkToCFile.write("}");
            BrainFkToCFile.flush();
            BrainFkToCFile.close();
        }
    }
}

void Brain::addWhiteSpaceIfNec(){
    for(int z = 0; z < whileCounter; z++){
        BrainFkToCFile.write("    ");
    }
}
