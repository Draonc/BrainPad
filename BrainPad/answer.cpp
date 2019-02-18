#include "answer.h"
#include "ui_answer.h"

QString answer;
Answer::Answer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Answer)
{
    ui->setupUi(this);
    ui->AnswerInput->show();
    ui->Enter->show();
}

Answer::~Answer()
{
    delete ui;
}

void Answer::on_Enter_clicked()
{
    answer = ui->AnswerInput->text();
    this->close();
}

QString Answer:: returnAnswer(){
    return answer;
}
