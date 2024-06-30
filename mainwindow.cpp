#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "log_page.h"
#include "register_page.h"
#include "start_use.h"
#include "register_page.h"
#include "set_class.h"
#include "ui_set_class.h"
#include "add_dll.h"
#include "ui_add_dll.h"
#include "timer.h"
#include "window_titles.h"
#include "buttonstyles.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <choosetime.h>
#include <ui_choosetime.h>
#include <QListWidget>

QColor buttonColors[10] = {
    QColor(0xEAE4E9),
    QColor(0xFFF1E6),
    QColor(0xFDE2E4),
    QColor(0xFAD2E1),
    QColor(0xE2ECE9),
    QColor(0xBEE1E6),
    QColor(0xF0EFEB),
    QColor(0xDFE7FD),
    QColor(0xCDDAFD),
    QColor(0xE9EDC9),
/*
    QColor("#EAE4E9"),
    QColor("#FFF1E6"),
    QColor("#FDE2E4"),
    QColor("#FAD2E1"),
    QColor("#E2ECE9"),
    QColor("#BEE1E6"),
    QColor("#F0EFEB"),
    QColor("#DFE7FD"),
    QColor("#CDDAFD"),
    QColor("#E9EDC9"),
*/
};
std::map<QString, int> classNameToColorIndex;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mytimer(nullptr)
{
    ui->setupUi(this);
    days.append(ui->mon_date);
    days.append(ui->tue_date);
    days.append(ui->wedn_date);
    days.append(ui->thur_date);
    days.append(ui->fri_date);
    days.append(ui->sat_date);
    days.append(ui->sun_date);
    mon_class.append(ui->mon_bt1);
    mon_class.append(ui->mon_bt2);
    mon_class.append(ui->mon_bt3);
    mon_class.append(ui->mon_bt4);
    mon_class.append(ui->mon_bt5);
    mon_class.append(ui->mon_bt6);
    mon_class.append(ui->mon_bt7);
    mon_class.append(ui->mon_bt8);
    mon_class.append(ui->mon_bt9);
    mon_class.append(ui->mon_bt10);
    mon_class.append(ui->mon_bt11);
    mon_class.append(ui->mon_bt12);
    tue_class.append(ui->tue_bt1);
    tue_class.append(ui->tue_bt2);
    tue_class.append(ui->tue_bt3);
    tue_class.append(ui->tue_bt4);
    tue_class.append(ui->tue_bt5);
    tue_class.append(ui->tue_bt6);
    tue_class.append(ui->tue_bt7);
    tue_class.append(ui->tue_bt8);
    tue_class.append(ui->tue_bt9);
    tue_class.append(ui->tue_bt10);
    tue_class.append(ui->tue_bt11);
    tue_class.append(ui->tue_bt12);
    wedn_class.append(ui->wedn_bt1);
    wedn_class.append(ui->wedn_bt2);
    wedn_class.append(ui->wedn_bt3);
    wedn_class.append(ui->wedn_bt4);
    wedn_class.append(ui->wedn_bt5);
    wedn_class.append(ui->wedn_bt6);
    wedn_class.append(ui->wedn_bt7);
    wedn_class.append(ui->wedn_bt8);
    wedn_class.append(ui->wedn_bt9);
    wedn_class.append(ui->wedn_bt10);
    wedn_class.append(ui->wedn_bt11);
    wedn_class.append(ui->wedn_bt12);
    thur_class.append(ui->thur_bt1);
    thur_class.append(ui->thur_bt2);
    thur_class.append(ui->thur_bt3);
    thur_class.append(ui->thur_bt4);
    thur_class.append(ui->thur_bt5);
    thur_class.append(ui->thur_bt6);
    thur_class.append(ui->thur_bt7);
    thur_class.append(ui->thur_bt8);
    thur_class.append(ui->thur_bt9);
    thur_class.append(ui->thur_bt10);
    thur_class.append(ui->thur_bt11);
    thur_class.append(ui->thur_bt12);
    fri_class.append(ui->fri_bt1);
    fri_class.append(ui->fri_bt2);
    fri_class.append(ui->fri_bt3);
    fri_class.append(ui->fri_bt4);
    fri_class.append(ui->fri_bt5);
    fri_class.append(ui->fri_bt6);
    fri_class.append(ui->fri_bt7);
    fri_class.append(ui->fri_bt8);
    fri_class.append(ui->fri_bt9);
    fri_class.append(ui->fri_bt10);
    fri_class.append(ui->fri_bt11);
    fri_class.append(ui->fri_bt12);
    sat_class.append(ui->sat_bt1);
    sat_class.append(ui->sat_bt2);
    sat_class.append(ui->sat_bt3);
    sat_class.append(ui->sat_bt4);
    sat_class.append(ui->sat_bt5);
    sat_class.append(ui->sat_bt6);
    sat_class.append(ui->sat_bt7);
    sat_class.append(ui->sat_bt8);
    sat_class.append(ui->sat_bt9);
    sat_class.append(ui->sat_bt10);
    sat_class.append(ui->sat_bt11);
    sat_class.append(ui->sat_bt12);
    sun_class.append(ui->sun_bt1);
    sun_class.append(ui->sun_bt2);
    sun_class.append(ui->sun_bt3);
    sun_class.append(ui->sun_bt4);
    sun_class.append(ui->sun_bt5);
    sun_class.append(ui->sun_bt6);
    sun_class.append(ui->sun_bt7);
    sun_class.append(ui->sun_bt8);
    sun_class.append(ui->sun_bt9);
    sun_class.append(ui->sun_bt10);
    sun_class.append(ui->sun_bt11);
    sun_class.append(ui->sun_bt12);
    day_class.append(mon_class);
    day_class.append(tue_class);
    day_class.append(wedn_class);
    day_class.append(thur_class);
    day_class.append(fri_class);
    day_class.append(sat_class);
    day_class.append(sun_class);
    ui->dateEdit->setDate(QDate::currentDate());  //打开时自动设置为当前日期
    ui->ddl_1->setVisible(false);
    ui->ddl_2->setVisible(false);
    ui->ddl_3->setVisible(false);
    ui->ddl_4->setVisible(false);
    ui->ddl_5->setVisible(false);
    ui->ddl_6->setVisible(false);
    ui->ddl_7->setVisible(false);
    ddls.append(ui->ddl_1);
    ddls.append(ui->ddl_2);
    ddls.append(ui->ddl_3);
    ddls.append(ui->ddl_4);
    ddls.append(ui->ddl_5);
    ddls.append(ui->ddl_6);
    ddls.append(ui->ddl_7);
    // connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);

    this->setWindowTitle(Q_GLOBAL_STATIC_CLASS(WindowTitles).MAINWINDOW_WINDOW_TITLE);

    /*  // UI: Change button style after text edited. This feature might be ditched.
    for(int i = 0; i < 7; i++){
        for(int k = 0; k < 12; k++){
            auto& button = day_class[i][k];
            connect(button, &QPushButton::textChanged, this, [this, button]() {
                updateButtonStyle(button);
            });
        }
    }
    */
}

MainWindow::~MainWindow()
{
    delete ui;
    QApplication::quit();
}
void MainWindow::ad_ddl(QDate date, QTime time, QString thing){
    if(!is_exsit_ddl_table()){
        MainWindow::create_ddl_table();
    }
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    QSqlQuery query;
    QString insert = QString("INSERT INTO %1_ddl (date, time, thing) VALUES(:date, :time, :thing)").arg(username);
    query.prepare(insert);
    query.bindValue(":date", date.toString("yy-MM-dd"));
    query.bindValue(":time", time.toString("hh:mm"));
    query.bindValue(":thing", thing);
    if(!query.exec()){
        qDebug() << "插入ddl数据失败！";
    }
}
void MainWindow::update_ddl(){
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    for(int i = 0; i < 7; i++){
        QString dt = days[i]->text();
        QSqlQuery query;
        QString s = QString("SELECT * FROM %1_ddl WHERE date = '%2'").arg(username, dt);
        if(!query.exec(s)){
            qDebug() << "查询ddl是否存在，失败！！！";
        }
        else{
            QString res = "";
            while(query.next()){
                QString tem = query.value("thing").toString() + " " + query.value("time").toString() + '\n';
                res += tem;
            }
            if(res == ""){
                ddls[i]->setVisible(false);
            }
            else{
                ddls[i]->setVisible(true);
                res.chop(1);
            }
            ddls[i]->setToolTip(res);
        }
    }
}
void MainWindow::create_ddl_table(){
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");

    QSqlQuery query;
    QString create = QString(
                         "CREATE TABLE %1_ddl ("
                         "date TEXT, "
                         "time TEXT, "
                         "thing TEXT"
                         ")"
                         ).arg(username);

    qDebug() << "SQL Statement: " << create; // Print the SQL statement

    if(!query.exec(create)){
        qDebug() << "创建DDL表失败！";
        qDebug() << "SQL Error: " << query.lastError().text(); // Print the SQL error
    } else {
        qDebug() << "DDL table created successfully!";
    }
}
bool MainWindow::is_exsit_ddl_table(){
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    QSqlQuery query;
    QString search = QString("SELECT name FROM sqlite_master WHERE type = 'table' AND name = '%1_ddl'").arg(username);
    if(!query.exec(search)){
        qDebug() << "执行查询ddl表失败！";
    }
    if(query.next()){
        return true;
    }
    return false;
}
void MainWindow::on_go2date_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if(db.open()){
        qDebug() << "成功打开数据库";
    }
    else{
        qDebug() << "未能成功打开数据库";
    }
    QDate now_date = ui->dateEdit->date();
    int tem = now_date.dayOfWeek();
    QDate p_date = now_date.addDays(1 - tem);
    for(int i = 0; i < 7; i++){
        days[i]->setText(p_date.toString("yy-MM-dd"));
        if(p_date < now_date){
            days[i]->setStyleSheet("QLabel { background-color : rgb(144, 238, 144); }");
        }
        if(p_date > now_date){
            days[i]->setStyleSheet("QLabel { background-color : rgb(240, 128, 128); }");
        }
        if(p_date == now_date){
            days[i]->setStyleSheet("QLabel { background-color : rgb(173, 216, 230); }");
        }
        QSqlQuery query;
        QString search_date = QString("SELECT * FROM %1 WHERE date = '%2'").arg(username).arg(p_date.toString("yy-MM-dd"));
        if(!query.exec(search_date)){
            qDebug() << "查找过程执行错误" ;
        }
        if(query.next()){ // 已经存在这个日期
            qDebug() << "已经存在这个日期，并找到了！";
            for(int k = 0; k < 12; k++){
                QString classn = QString("class%1").arg(k + 1);
                day_class[i][k]->setText(query.value(classn).toString());
                updateButtonStyleIfNeeded(i, k);    // update button style for LOADED classes
            }
        }
        else{  // 不存在这个日期
            qDebug() << "没找到这个日期啊！";
            query.prepare("INSERT INTO " + username + " (date, class1, class2, class3, class4, class5, class6, class7, class8, class9, class10, class11, class12) "
                                                      "VALUES (:date, :class1, :class2, :class3, :class4, :class5, :class6, :class7, :class8, :class9, :class10, :class11, :class12)");
            query.bindValue(":date", p_date.toString("yy-MM-dd"));
            for(int k = 0; k < 12; k++){
                QString c = QString(":class%1").arg(k + 1);
                query.bindValue(c," ");
                day_class[i][k]->setText(" ");
            }
            if(!query.exec()){
                qDebug() << "插入错误";
            }
            else{
                qDebug() << "成功插入";
            }
        }
        MainWindow::update_ddl();
        p_date = p_date.addDays(1);
    }
}
void MainWindow::expand_class(const QDate start,const QDate end){
    QDate p_date = start;
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if(db.open()){
        qDebug() << "成功打开数据库";
    }
    else{
        qDebug() << "未能成功打开数据库";
    }
    if(end < start){
        QMessageBox::critical(this, "提示", "错误！开始日期晚于结束日期");
        return;
    }
    while(p_date != end.addDays(1)){
        int tem = p_date.dayOfWeek() - 1;
        QSqlQuery query;
        QString search_date = QString("SELECT * FROM %1 WHERE date = '%2'").arg(username).arg(p_date.toString("yy-MM-dd"));
        if(!query.exec(search_date)){
            qDebug() << "查找过程执行错误" ;
        }
        if(query.next()){ // 已经存在这个日期
            qDebug() << "已经存在这个日期，并找到了！";
            for(int k = 0; k < 12; k++){
                QString updateSql = QString(
                                        "UPDATE %1 SET "
                                        "class%2 = ? "
                                        "WHERE date = ?"
                                        ).arg(username).arg(k + 1);

                query.prepare(updateSql);

                // 绑定要更新的数据
                query.addBindValue(day_class[tem][k]->text());  // 新的值
                query.addBindValue(p_date.toString("yy-MM-dd"));  // 日期
                // 执行SQL语句
                if (!query.exec()) {
                    // 处理错误
                    qDebug() << "未能成功更新";
                }
            }
        }
        else{  // 不存在这个日期
            qDebug() << "没找到这个日期啊！";
            query.prepare("INSERT INTO " + username + " (date, class1, class2, class3, class4, class5, class6, class7, class8, class9, class10, class11, class12) "
                                                      "VALUES (:date, :class1, :class2, :class3, :class4, :class5, :class6, :class7, :class8, :class9, :class10, :class11, :class12)");
            query.bindValue(":date", p_date.toString("yy-MM-dd"));
            for(int k = 0; k < 12; k++){
                QString c = QString(":class%1").arg(k + 1);
                query.bindValue(c, day_class[tem][k]->text());
            }
            if(!query.exec()){
                qDebug() << "插入错误";
            }
            else{
                qDebug() << "成功插入";
            }
        }
        p_date = p_date.addDays(1);
    }
}

// make the compiler happy
void MainWindow::on_pushButton_5_clicked()
{

}

void MainWindow::update_name(QString name, int which_day, int which_class){
    day_class[which_day][which_class - 1]->setText(name);
}
void MainWindow::add_class(QString t_date, int w_class, QString prev_n, QString un)
{
    qDebug("add_class was called with params: ");
    qDebug() << t_date << ' ' << w_class << ' ' << prev_n << ' ' << un;
    int rec = 0;
    for(int i = 0; i < 7; i++){
        if(days[i]->text() == t_date){
            rec = i;
            break;
        }
    }

    ClassInfo classInfo;
    int key = 100 * rec + w_class;
    if (classInfoMap.contains(key)) {
        classInfo = classInfoMap[key];
        qDebug("Found class key; class name is: ");
        qDebug() << classInfo.name;
    } else {
        classInfo = {prev_n, 0, 0, 0}; // Default values
        qDebug("Not Found class key; class name is: ");
        qDebug() << prev_n;
    }

    set = new set_class(classInfo.name, classInfo.hours, classInfo.minutes, classInfo.seconds, this);
    set->the_date = t_date;
    set->which_class = w_class;
    set->username = un;
    set->prev_name = prev_n;
    set->which_day = rec;   // rec was calculated earlier
    // set->set_lineedit(); // don't know why this line appears here, should never be called without param.
    set->show();
    connect(set, &set_class::update_class, this, &MainWindow::update_class_info);
}

void MainWindow::update_class_info(QString name, int hours, int minutes, int seconds, int which_day, int which_class)
{
    qDebug() << "Updated class: " << name << " Duration: " << hours << "h " << minutes << "m " << seconds << "s";

    day_class[which_day][which_class - 1]->setText(name);

    // Update button style if class name is not null
    updateButtonStyleIfNeeded(which_day, which_class - 1);

    int key = 100 * which_day + which_class;
    classInfoMap[key] = {name, hours, minutes, seconds};
}

void MainWindow::updateButtonStyleIfNeeded(int which_day, int which_class)
{
    // First, the class name also comes into play.
    QString className = day_class[which_day][which_class]->text().trimmed();    // CRUCIAL! removes whitespace.

    // CASE 1: Reset to default style if class is cleared
    if (className.isEmpty()) {
        day_class[which_day][which_class]->setStyleSheet("");
        return;
    }

    // CASE 2: Update button style if class name is not null

    // get the color index
    if (classNameToColorIndex.find(className) == classNameToColorIndex.end()) {
        int newIndex = classNameToColorIndex.size();
        classNameToColorIndex[className] = newIndex;
    }
    int colorIndex = classNameToColorIndex[className] % (sizeof(buttonColors) / sizeof(buttonColors[0])); // wrap around

    // get the QSS
    QColor bgColor = buttonColors[colorIndex];
    QString qss = generateButtonQSS(bgColor);

    // use the QSS
    day_class[which_day][which_class]->setStyleSheet(qss);
}


void MainWindow::on_mon_bt1_clicked()
{
    MainWindow::add_class(days[0]->text(), 1, mon_class[0]->text(),username);
}


void MainWindow::on_mon_bt2_clicked()
{
    MainWindow::add_class(days[0]->text(), 2, mon_class[1]->text(),username);
}


void MainWindow::on_mon_bt3_clicked()
{
    MainWindow::add_class(days[0]->text(), 3, mon_class[2]->text(),username);
}


void MainWindow::on_mon_bt4_clicked()
{
    MainWindow::add_class(days[0]->text(), 4, mon_class[3]->text(),username);
}


void MainWindow::on_mon_bt5_clicked()
{
    MainWindow::add_class(days[0]->text(), 5, mon_class[4]->text(),username);
}


void MainWindow::on_mon_bt6_clicked()
{
    MainWindow::add_class(days[0]->text(), 6, mon_class[5]->text(),username);
}


void MainWindow::on_mon_bt7_clicked()
{
    MainWindow::add_class(days[0]->text(), 7, mon_class[6]->text(),username);
}


void MainWindow::on_mon_bt8_clicked()
{
    MainWindow::add_class(days[0]->text(), 8, mon_class[7]->text(),username);
}


void MainWindow::on_mon_bt9_clicked()
{
    MainWindow::add_class(days[0]->text(), 9, mon_class[8]->text(),username);
}


void MainWindow::on_mon_bt10_clicked()
{
    MainWindow::add_class(days[0]->text(), 10, mon_class[9]->text(),username);
}


void MainWindow::on_mon_bt11_clicked()
{
    MainWindow::add_class(days[0]->text(), 11, mon_class[10]->text(),username);
}


void MainWindow::on_mon_bt12_clicked()
{
    MainWindow::add_class(days[0]->text(), 12, mon_class[11]->text(),username);
}


void MainWindow::on_tue_bt1_clicked()
{
    MainWindow::add_class(days[1]->text(), 1, tue_class[0]->text(),username);
}


void MainWindow::on_tue_bt2_clicked()
{
    MainWindow::add_class(days[1]->text(), 2, tue_class[1]->text(),username);
}


void MainWindow::on_tue_bt3_clicked()
{
    MainWindow::add_class(days[1]->text(), 3, tue_class[2]->text(),username);
}


void MainWindow::on_tue_bt4_clicked()
{
    MainWindow::add_class(days[1]->text(), 4, tue_class[3]->text(),username);
}


void MainWindow::on_tue_bt5_clicked()
{
    MainWindow::add_class(days[1]->text(), 5, tue_class[4]->text(),username);
}


void MainWindow::on_tue_bt6_clicked()
{
    MainWindow::add_class(days[1]->text(), 6, tue_class[5]->text(),username);
}


void MainWindow::on_tue_bt7_clicked()
{
    MainWindow::add_class(days[1]->text(), 7, tue_class[6]->text(),username);
}


void MainWindow::on_tue_bt8_clicked()
{
    MainWindow::add_class(days[1]->text(), 8, tue_class[7]->text(),username);
}


void MainWindow::on_tue_bt9_clicked()
{
    MainWindow::add_class(days[1]->text(), 9, tue_class[8]->text(),username);
}


void MainWindow::on_tue_bt10_clicked()
{
    MainWindow::add_class(days[1]->text(), 10, tue_class[9]->text(),username);
}


void MainWindow::on_tue_bt11_clicked()
{
    MainWindow::add_class(days[1]->text(), 11, tue_class[10]->text(),username);
}


void MainWindow::on_tue_bt12_clicked()
{
    MainWindow::add_class(days[1]->text(), 12, tue_class[11]->text(),username);
}


void MainWindow::on_wedn_bt1_clicked()
{
    MainWindow::add_class(days[2]->text(), 1, wedn_class[0]->text(),username);
}


void MainWindow::on_wedn_bt2_clicked()
{
    MainWindow::add_class(days[2]->text(), 2, wedn_class[1]->text(),username);
}


void MainWindow::on_wedn_bt3_clicked()
{
    MainWindow::add_class(days[2]->text(), 3, wedn_class[2]->text(),username);
}


void MainWindow::on_wedn_bt4_clicked()
{
    MainWindow::add_class(days[2]->text(), 4, wedn_class[3]->text(),username);
}


void MainWindow::on_wedn_bt5_clicked()
{
    MainWindow::add_class(days[2]->text(), 5, wedn_class[4]->text(),username);
}


void MainWindow::on_wedn_bt6_clicked()
{
    MainWindow::add_class(days[2]->text(), 6, wedn_class[5]->text(),username);
}


void MainWindow::on_wedn_bt7_clicked()
{
    MainWindow::add_class(days[2]->text(), 7, wedn_class[6]->text(),username);
}


void MainWindow::on_wedn_bt8_clicked()
{
    MainWindow::add_class(days[2]->text(), 8, wedn_class[7]->text(),username);
}


void MainWindow::on_wedn_bt9_clicked()
{
    MainWindow::add_class(days[2]->text(), 9, wedn_class[8]->text(),username);
}


void MainWindow::on_wedn_bt10_clicked()
{
    MainWindow::add_class(days[2]->text(), 10, wedn_class[9]->text(),username);
}


void MainWindow::on_wedn_bt11_clicked()
{
    MainWindow::add_class(days[2]->text(), 11, wedn_class[10]->text(),username);
}


void MainWindow::on_wedn_bt12_clicked()
{
    MainWindow::add_class(days[2]->text(), 12, wedn_class[11]->text(),username);
}


void MainWindow::on_thur_bt1_clicked()
{
    MainWindow::add_class(days[3]->text(), 1, thur_class[0]->text(),username);
}


void MainWindow::on_thur_bt2_clicked()
{
    MainWindow::add_class(days[3]->text(), 2, thur_class[1]->text(),username);
}


void MainWindow::on_thur_bt3_clicked()
{
    MainWindow::add_class(days[3]->text(), 3, thur_class[2]->text(),username);
}


void MainWindow::on_thur_bt4_clicked()
{
    MainWindow::add_class(days[3]->text(), 4, thur_class[3]->text(),username);
}


void MainWindow::on_thur_bt5_clicked()
{
    MainWindow::add_class(days[3]->text(), 5, thur_class[4]->text(),username);
}


void MainWindow::on_thur_bt6_clicked()
{
    MainWindow::add_class(days[3]->text(), 6, thur_class[5]->text(),username);
}


void MainWindow::on_thur_bt7_clicked()
{
    MainWindow::add_class(days[3]->text(), 7, thur_class[6]->text(),username);
}


void MainWindow::on_thur_bt8_clicked()
{
    MainWindow::add_class(days[3]->text(), 8, thur_class[7]->text(),username);
}


void MainWindow::on_thur_bt9_clicked()
{
    MainWindow::add_class(days[3]->text(), 9, thur_class[8]->text(),username);
}


void MainWindow::on_thur_bt10_clicked()
{
    MainWindow::add_class(days[3]->text(), 10, thur_class[9]->text(),username);
}


void MainWindow::on_thur_bt11_clicked()
{
    MainWindow::add_class(days[3]->text(), 11, thur_class[10]->text(),username);
}


void MainWindow::on_thur_bt12_clicked()
{
    MainWindow::add_class(days[3]->text(), 12, thur_class[11]->text(),username);
}


void MainWindow::on_fri_bt1_clicked()
{
    MainWindow::add_class(days[4]->text(), 1, fri_class[0]->text(),username);
}


void MainWindow::on_fri_bt2_clicked()
{
    MainWindow::add_class(days[4]->text(), 2, fri_class[1]->text(),username);
}


void MainWindow::on_fri_bt3_clicked()
{
    MainWindow::add_class(days[4]->text(), 3, fri_class[2]->text(),username);
}


void MainWindow::on_fri_bt4_clicked()
{
    MainWindow::add_class(days[4]->text(), 4, fri_class[3]->text(),username);
}


void MainWindow::on_fri_bt5_clicked()
{
    MainWindow::add_class(days[4]->text(), 5, fri_class[4]->text(),username);
}


void MainWindow::on_fri_bt6_clicked()
{
    MainWindow::add_class(days[4]->text(), 6, fri_class[5]->text(),username);
}


void MainWindow::on_fri_bt7_clicked()
{
    MainWindow::add_class(days[4]->text(), 7, fri_class[6]->text(),username);
}


void MainWindow::on_fri_bt8_clicked()
{
    MainWindow::add_class(days[4]->text(), 8, fri_class[7]->text(),username);
}


void MainWindow::on_fri_bt9_clicked()
{
    MainWindow::add_class(days[4]->text(), 9, fri_class[8]->text(),username);
}


void MainWindow::on_fri_bt10_clicked()
{
    MainWindow::add_class(days[4]->text(), 10, fri_class[9]->text(),username);
}


void MainWindow::on_fri_bt11_clicked()
{
    MainWindow::add_class(days[4]->text(), 11, fri_class[10]->text(),username);
}


void MainWindow::on_fri_bt12_clicked()
{
    MainWindow::add_class(days[4]->text(), 12, fri_class[11]->text(),username);
}


void MainWindow::on_sat_bt1_clicked()
{
    MainWindow::add_class(days[5]->text(), 1, sat_class[0]->text(),username);
}


void MainWindow::on_sat_bt2_clicked()
{
    MainWindow::add_class(days[5]->text(), 2, sat_class[1]->text(),username);
}


void MainWindow::on_sat_bt3_clicked()
{
    MainWindow::add_class(days[5]->text(), 3, sat_class[2]->text(),username);
}


void MainWindow::on_sat_bt4_clicked()
{
    MainWindow::add_class(days[5]->text(), 4, sat_class[3]->text(),username);
}


void MainWindow::on_sat_bt5_clicked()
{
    MainWindow::add_class(days[5]->text(), 5, sat_class[4]->text(),username);
}


void MainWindow::on_sat_bt6_clicked()
{
    MainWindow::add_class(days[5]->text(), 6, sat_class[5]->text(),username);
}


void MainWindow::on_sat_bt7_clicked()
{
    MainWindow::add_class(days[5]->text(), 7, sat_class[6]->text(),username);
}


void MainWindow::on_sat_bt8_clicked()
{
    MainWindow::add_class(days[5]->text(), 8, sat_class[7]->text(),username);
}


void MainWindow::on_sat_bt9_clicked()
{
    MainWindow::add_class(days[5]->text(), 9, sat_class[8]->text(),username);
}


void MainWindow::on_sat_bt10_clicked()
{
    MainWindow::add_class(days[5]->text(), 10, sat_class[9]->text(),username);
}


void MainWindow::on_sat_bt11_clicked()
{
    MainWindow::add_class(days[5]->text(), 11, sat_class[10]->text(),username);
}


void MainWindow::on_sat_bt12_clicked()
{
    MainWindow::add_class(days[5]->text(), 12, sat_class[11]->text(),username);
}


void MainWindow::on_sun_bt1_clicked()
{
    MainWindow::add_class(days[6]->text(), 1, sun_class[0]->text(),username);
}


void MainWindow::on_sun_bt2_clicked()
{
    MainWindow::add_class(days[6]->text(), 2, sun_class[1]->text(),username);
}


void MainWindow::on_sun_bt3_clicked()
{
    MainWindow::add_class(days[6]->text(), 3, sun_class[2]->text(),username);
}


void MainWindow::on_sun_bt4_clicked()
{
    MainWindow::add_class(days[6]->text(), 4, sun_class[3]->text(),username);
}


void MainWindow::on_sun_bt5_clicked()
{
    MainWindow::add_class(days[6]->text(), 5, sun_class[4]->text(),username);
}


void MainWindow::on_sun_bt6_clicked()
{
    MainWindow::add_class(days[6]->text(), 6, sun_class[5]->text(),username);
}


void MainWindow::on_sun_bt7_clicked()
{
    MainWindow::add_class(days[6]->text(), 7, sun_class[6]->text(),username);
}


void MainWindow::on_sun_bt8_clicked()
{
    MainWindow::add_class(days[6]->text(), 8, sun_class[7]->text(),username);
}


void MainWindow::on_sun_bt9_clicked()
{
    MainWindow::add_class(days[6]->text(), 9, sun_class[8]->text(),username);
}


void MainWindow::on_sun_bt10_clicked()
{
    MainWindow::add_class(days[6]->text(), 10, sun_class[9]->text(),username);
}


void MainWindow::on_sun_bt11_clicked()
{
    MainWindow::add_class(days[6]->text(), 11, sun_class[10]->text(),username);
}


void MainWindow::on_sun_bt12_clicked()
{
    MainWindow::add_class(days[6]->text(), 12, sun_class[11]->text(),username);
}

void MainWindow::on_expand_button_clicked()
{
    Choosetime* ctim = new Choosetime(this);
    connect(ctim, &Choosetime::send_date, this, &MainWindow::expand_class);
    ctim->show();
}

// make the compiler happy
void MainWindow::on_pushButton_4_clicked()
{
    delete this;
}




void MainWindow::on_set_ddl_clicked()
{
    Add_dll* ad = new Add_dll(this);
    ad->show();
    connect(ad, &Add_dll::signal_add_ddl, this, &MainWindow::ad_ddl);
    connect(ad, &Add_dll::signal_add_ddl, this, &MainWindow::update_ddl);
}


void MainWindow::on_exit_button_clicked()
{
    delete this;
}


void MainWindow::on_ddl_1_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除ddl", "你确定要删除这条ddl吗?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        QSqlQuery query;
        QString del = QString("DELETE FROM %1_ddl WHERE date = '%2'").arg(username, days[0]->text());
        if(!query.exec(del)){
            qDebug() << "删除操作执行失败";
        }
        MainWindow::update_ddl();
    }
}


void MainWindow::on_ddl_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除ddl", "你确定要删除这条ddl吗?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        QSqlQuery query;
        QString del = QString("DELETE FROM %1_ddl WHERE date = '%2'").arg(username, days[1]->text());
        if(!query.exec(del)){
            qDebug() << "删除操作执行失败";
        }
        MainWindow::update_ddl();
    }
}


void MainWindow::on_ddl_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除ddl", "你确定要删除这条ddl吗?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        QSqlQuery query;
        QString del = QString("DELETE FROM %1_ddl WHERE date = '%2'").arg(username, days[2]->text());
        if(!query.exec(del)){
            qDebug() << "删除操作执行失败";
        }
        MainWindow::update_ddl();
    }
}


void MainWindow::on_ddl_4_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除ddl", "你确定要删除这条ddl吗?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        QSqlQuery query;
        QString del = QString("DELETE FROM %1_ddl WHERE date = '%2'").arg(username, days[3]->text());
        if(!query.exec(del)){
            qDebug() << "删除操作执行失败";
        }
        MainWindow::update_ddl();
    }
}


void MainWindow::on_ddl_5_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除ddl", "你确定要删除这条ddl吗?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        QSqlQuery query;
        QString del = QString("DELETE FROM %1_ddl WHERE date = '%2'").arg(username, days[4]->text());
        if(!query.exec(del)){
            qDebug() << "删除操作执行失败";
        }
        MainWindow::update_ddl();
    }
}


void MainWindow::on_ddl_6_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除ddl", "你确定要删除这条ddl吗?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        QSqlQuery query;
        QString del = QString("DELETE FROM %1_ddl WHERE date = '%2'").arg(username, days[5]->text());
        if(!query.exec(del)){
            qDebug() << "删除操作执行失败";
        }
        MainWindow::update_ddl();
    }
}


void MainWindow::on_ddl_7_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除ddl", "你确定要删除这条ddl吗?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        QSqlQuery query;
        QString del = QString("DELETE FROM %1_ddl WHERE date = '%2'").arg(username, days[6]->text());
        if(!query.exec(del)){
            qDebug() << "删除操作执行失败";
        }
        MainWindow::update_ddl();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!mytimer) { // robustness
        mytimer = new timer(this);
        qDebug("Created timer");
    }
    // mytimer->setGeometry(this->geometry());
    mytimer->show();
    qDebug("Shown timer");

    this->hide();
}

