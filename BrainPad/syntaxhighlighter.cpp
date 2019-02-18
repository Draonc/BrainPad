#include <QtGui>

    #include "syntaxhighlighter.h"

    Highlighter::Highlighter(QTextDocument *parent): QSyntaxHighlighter(parent)
    {
        HighlightingRule rule;

        whilerightFormat.setForeground(Qt::red);
        rule.pattern = QRegExp("\\[");
        rule.format = whilerightFormat;
        highlightingRules.append(rule);

        whileleftFormat.setForeground(Qt::red);
        rule.pattern = QRegExp("\\]");
        rule.format = whileleftFormat;
        highlightingRules.append(rule);

        commentFormat.setForeground(Qt::darkCyan);
        rule.pattern = QRegExp(" ");
        rule.format = commentFormat;
        highlightingRules.append(rule);


        pointerrightFormat.setForeground(QColor(204, 85, 0, 255));
        rule.pattern = QRegExp(">");
        rule.format = pointerrightFormat;
        highlightingRules.append(rule);

        pointerleftFormat.setForeground(QColor(204, 85, 0, 255));
        rule.pattern = QRegExp("<");
        rule.format = pointerleftFormat;
        highlightingRules.append(rule);

        plusFormat.setForeground(Qt::black);
        rule.pattern = QRegExp("\\+");
        rule.format = plusFormat;
        highlightingRules.append(rule);

        minusFormat.setForeground(Qt::black);
        rule.pattern = QRegExp("-");
        rule.format = minusFormat;
        highlightingRules.append(rule);

        outputFormat.setForeground(Qt::darkCyan);
        rule.pattern = QRegExp("\\.");
        rule.format = outputFormat;
        highlightingRules.append(rule);

        inputFormat.setForeground(Qt::green);
        rule.pattern = QRegExp(",");
        rule.format = inputFormat;
        highlightingRules.append(rule);

        commentStartExpression = QRegExp("/\\*");
        commentEndExpression = QRegExp("\\*/");
    }

    void Highlighter::highlightBlock(const QString &text)
    {
        foreach (HighlightingRule rule, highlightingRules) {
            QRegExp expression(rule.pattern);
            int index = text.indexOf(expression);
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = text.indexOf(expression, index + length);
            }
        }
        setCurrentBlockState(0);

        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = text.indexOf(commentStartExpression);

        while (startIndex >= 0) {
           int endIndex = text.indexOf(commentEndExpression, startIndex);
           int commentLength;
           if (endIndex == -1) {
               setCurrentBlockState(1);
               commentLength = text.length() - startIndex;
           } else {
               commentLength = endIndex - startIndex
                               + commentEndExpression.matchedLength();
           }
           setFormat(startIndex, commentLength, commentFormat);
           startIndex = text.indexOf(commentStartExpression,
                                                   startIndex + commentLength);
        }
    }


    void Highlighter::highlightError(int errors[]){
        errorFormat.setForeground(Qt::darkBlue);
        errorFormat.setFontWeight(QFont::Bold);






        setFormat(2, 1, errorFormat);
       // int startIndex;
        //for(int i = 0; i<500; i++){
         //   if(errors[i] > 0){
          //      printf("Error %d\n", errors[i]);
           //     startIndex = errors[i];
            //    setFormat(startIndex, 1, Qt::darkBlue);
            //}
       // }
    }
