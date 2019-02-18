#include "consoledialog.h"
#include "ui_consoledialog.h"

ConsoleDialog::ConsoleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConsoleDialog)
{
    ui->setupUi(this);

    ui->textEditConsole->setAutoFillBackground(true);
    ui->textEditConsole->setStyleSheet("font:12pt;");
    ui->textEditConsole->show();
}

ConsoleDialog::~ConsoleDialog()
{
    delete ui;
}


void ConsoleDialog::readInfo(QString info){
    ui->textEditConsole->setPlainText(info);
}
