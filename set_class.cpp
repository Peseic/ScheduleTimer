#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "log_page.h"
#include "register_page.h"
#include "start_use.h"
#include "register_page.h"
#include "set_class.h"
#include "ui_set_class.h"
#include "window_titles.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
set_class::set_class(QString p_name, int hours, int minutes, int seconds, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::set_class), prev_name(p_name)
{

    ui->setupUi(this);
    ui->lineEdit->setText(prev_name);

    ui->setclass_Spinbox_h->setValue(hours);
    ui->setclass_Spinbox_m->setValue(minutes);
    ui->setclass_Spinbox_s->setValue(seconds);

    connect(ui->pushButton, &QPushButton::clicked, this, &set_class::on_pushButton_clicked);

    this->setWindowTitle(Q_GLOBAL_STATIC_CLASS(WindowTitles).SET_CLASS_WINDOW_TITLE);
}

set_class::~set_class()
{
    delete ui;
}
void set_class::set_lineedit(){
    ui->lineEdit->setText(prev_name);
}
void set_class::on_pushButton_clicked()
{
    QString updateSql = QString(
                            "UPDATE %1 SET "
                            "class%2 = ? "
                            "WHERE date = ?"
                            ).arg(username).arg(which_class);

    QSqlQuery query;
    query.prepare(updateSql);

    // 绑定要更新的数据
    query.addBindValue(ui->lineEdit->text());  // 新的值
    query.addBindValue(the_date);  // 日期

    // 执行SQL语句
    if (!query.exec()) {
        // 处理错误
    }

    QString name = ui->lineEdit->text();
    int hours = ui->setclass_Spinbox_h->value();
    int minutes = ui->setclass_Spinbox_m->value();
    int seconds = ui->setclass_Spinbox_s->value();
    emit update_class(name, hours, minutes, seconds, which_day, which_class);
    // emit update_class(ui->lineEdit->text(), which_day, which_class);
    delete this;
}


void set_class::on_pushButton_2_clicked()
{
    delete this;
}

