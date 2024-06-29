#include "choosetime.h"
#include "ui_choosetime.h"
#include "window_titles.h"
#include <QDate>
Choosetime::Choosetime(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Choosetime)
{
    ui->setupUi(this);
    ui->dateEdit_start->setDate(QDate::currentDate());
    ui->dateEdit_end->setDate(QDate::currentDate());

    this->setWindowTitle(Q_GLOBAL_STATIC_CLASS(WindowTitles).CHOOSETIME_WINDOW_TITLE);
}

Choosetime::~Choosetime()
{
    delete ui;
}

void Choosetime::on_pushButton_clicked()
{
    emit send_date(ui->dateEdit_start->date(), ui->dateEdit_end->date());
    delete this;
}


void Choosetime::on_pushButton_2_clicked()
{
    delete this;
}

