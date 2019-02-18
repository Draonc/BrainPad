#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>

#include "syntaxhighlighter.h"
#include "lex.h"
#include "brainfktoc.h"
#include "answer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void output(char outputLine);

private slots:
    void on_actionPaste_triggered();

    void on_actionDelete_triggered();

    void on_actionSelect_All_triggered();

    void on_actionDefault_Mode_triggered();

    void on_actionDark_Mode_triggered();

    void on_actionUndo_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionRedo_triggered();

    void on_actionAbout_triggered();

    void on_actionComment_Code_triggered();

    int *on_actionParse_triggered();

    void on_actionInterperet_triggered();

    void on_actionConvert_triggered();

private:
    Ui::MainWindow *ui;
    QString mFilename;
    QString text;
    Lex lex;
    Brain Converter;
    Answer answer;
    Highlighter *highlighter;
};

#endif // MAINWINDOW_H
