#include "timer_popup.h"
#include "ui_timer_popup.h"
#include "window_titles.h"

timer_popup::timer_popup(QWidget *parent, QString _mode)
    : QDialog(parent)
    , ui(new Ui::timer_popup)
    , mode(_mode)
{
    ui->setupUi(this);
    ui->whatnext_label->setText("");
    if (mode == "tomato") {
        ui->whatnext_label->setText("休息一下吧~ ");
    }
    else if (mode == "rest") {
        ui->whatnext_label->setText("不再来个番茄吗? ");
    }

    this->setWindowTitle(Q_GLOBAL_STATIC_CLASS(WindowTitles).TIMER_POPUP_WINDOW_TITLE);
}

timer_popup::~timer_popup()
{
    delete ui;
}

void timer_popup::on_pushButton_clicked()
{
    delete this;
}

