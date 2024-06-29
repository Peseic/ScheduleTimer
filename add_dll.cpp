#include "add_dll.h"
#include "ui_add_dll.h"
#include "window_titles.h"
#include <QDate>
Add_dll::Add_dll(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_dll)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    this->setWindowTitle(Q_GLOBAL_STATIC_CLASS(WindowTitles).ADD_DLL_WINDOW_TITLE);
}

Add_dll::~Add_dll()
{
    delete ui;
}

void Add_dll::on_pushButton_2_clicked()
{
    delete this;
}


void Add_dll::on_pushButton_clicked()
{
    emit signal_add_ddl(ui->dateEdit->date(), ui->timeEdit->time(), ui->lineEdit->text());
    delete this;
}

