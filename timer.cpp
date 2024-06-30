#include "timer.h"
#include "ui_timer.h"
#include "timer_popup.h"
#include "mainwindow.h"
#include "window_titles.h"


QColor default_gray = QColor(240, 240, 240);
QColor light_red = QColor(255, 182, 193);
QColor light_green = QColor(144, 238, 144);
QColor lilac = QColor(237, 200, 255);

bool accelerate = true;
int ms_in_s = accelerate ? 50 : 1000;
int color_gradient_time = 1000;         // milliseconds
int color_gradient_update_time = 30;    // milliseconds

// DBG macros
bool colorDBG = false;

timer::timer(MainWindow *parent)
    : QWidget(nullptr) // Ensure the timer window is a top-level window
    , ui(new Ui::timer)
    , mainWindow(parent)
    , mode("none")
    , colorTimer(new QTimer(this))
    , duration(0)
    , elapsed(0)
    , currentTimeTimer(new QTimer(this))
    , currentTimeTimerState("active")
{
    ui->setupUi(this);
    connect(&tomato_timer, SIGNAL(timeout()), this, SLOT(timeout_slot()));
    connect(colorTimer, SIGNAL(timeout()), this, SLOT(updateBackgroundColor()));

    connect(currentTimeTimer, &QTimer::timeout, this, &timer::updateCurrentTime);

    time.setHMS(0, 0, 0, 0);
    // ui->showTime->setText("00:00:00");
    // ui->pauseLabel->setText("");

    on_timer_reset_bt_clicked();    // display current time at init

    if (accelerate) {
        ui->accelerateLabel->setText("Note: Accelerate mode is on for demonstration purposes.");
    }

    set_customHMS_visibility(false);

    this->setWindowTitle(Q_GLOBAL_STATIC_CLASS(WindowTitles).TIMER_WINDOW_TITLE);
}

timer::~timer()
{
    delete ui;
    delete currentTimeTimer;
}

void timer::on_pushButton_clicked()
{
    currentTimeTimerState = "inactive"; // should be inactive most of the time

    this->hide();
    if (mainWindow) {
        mainWindow->show();
    }
}

void timer::timeout_slot()
{
    qDebug("timer ticked 1 second");
    time = time.addSecs(-1);

    if (time.hour() == 0 && time.minute() == 0 && time.second() == 0) {
        ui->showTime->setText(time.toString("mm:ss"));
        ui->pauseLabel->setText("TIME IS UP! ");
        // timer ended
        tomato_timer.stop();
        setBackgroundColor(default_gray, color_gradient_time);
        timer_popup *popup = new timer_popup(this, mode);
        connect(popup, &timer_popup::tomatoToRest, this, &timer::on_timer_rest_bt_clicked);       // auto mode switch
        connect(popup, &timer_popup::restToTomato, this, &timer::on_timer_tomato_bt_clicked);     // auto mode switch
        connect(popup, &timer_popup::normalEnd, this, &timer::on_timer_reset_bt_clicked);         // auto back to display current time
        popup->exec();

        // time.setHMS(0, 0, 0, 0);
        // updateCurrentTime();
        ui->pauseLabel->setText("");
    }

    if (time.hour() == 0) {
        ui->showTime->setText(time.toString("mm:ss"));
    }
    else {
        ui->showTime->setText(time.toString("hh:mm:ss"));
    }

}

void timer::on_timer_tomato_bt_clicked()
{
    currentTimeTimerState = "inactive"; // should be inactive most of the time

    qDebug("tomato button called");
    mode = "tomato";
    tomato_timer.stop();
    ui->pauseLabel->setText("");
    set_customHMS_visibility(false);
    // POMODORO: count down from 25 mins
    time.setHMS(0, 25, 0, 0);
    ui->showTime->setText("25:00");

    ui->showTime->update();

    setBackgroundColor(light_red, color_gradient_time);

    qDebug() << "Time set to:" << time.toString("mm:ss");
}

void timer::on_timer_rest_bt_clicked()
{
    currentTimeTimerState = "inactive"; // should be inactive most of the time

    qDebug("rest button called");
    mode = "rest";
    tomato_timer.stop();
    ui->pauseLabel->setText("");
    set_customHMS_visibility(false);
    // REST: count down from 5 mins
    time.setHMS(0, 5, 0, 0);
    ui->showTime->setText("05:00");

    setBackgroundColor(light_green, color_gradient_time);
}

void timer::on_timer_custom_bt_clicked()
{
    currentTimeTimerState = "inactive"; // should be inactive most of the time

    mode = "custom";
    tomato_timer.stop();
    ui->pauseLabel->setText("");
    // CUSTOM: count down from what user specifies
    set_customHMS_visibility(true);
    ui->showTime->setText("");

    ui->spinBox_h->setValue(0);
    ui->spinBox_m->setValue(0);
    ui->spinBox_s->setValue(0);

    setBackgroundColor(lilac, color_gradient_time);
}


void timer::on_timer_start_bt_clicked()
{
    currentTimeTimerState = "inactive"; // should be inactive most of the time

    if (ui->spinBox_h->isVisible()) {   // is in custom mode
        int hours = ui->spinBox_h->value();
        int minutes = ui->spinBox_m->value();
        int seconds = ui->spinBox_s->value();
        time.setHMS(hours, minutes, seconds, 0);
        set_customHMS_visibility(false);
        if (time.hour() == 0) {
            ui->showTime->setText(time.toString("mm:ss"));
        }
        else {
            ui->showTime->setText(time.toString("hh:mm:ss"));
        }
    }
    tomato_timer.start(ms_in_s);
    ui->pauseLabel->setText("");
}


void timer::on_timer_stop_bt_clicked()
{
    currentTimeTimerState = "inactive"; // should be inactive most of the time

    tomato_timer.stop();
    ui->pauseLabel->setText("PAUSED");
}


void timer::on_timer_reset_bt_clicked()
{
    currentTimeTimerState = "active";

    tomato_timer.stop();
    ui->pauseLabel->setText("");

    if (currentTimeTimerState == "active") {    // when idle, display current time
        currentTimeTimer->start(1000); // upd every 1000 ms = 1 second
        updateCurrentTime();
    }

    setBackgroundColor(default_gray, color_gradient_time);
}

void timer::updateCurrentTime()
{
    if (currentTimeTimerState == "active") {
        qDebug("updateCurrentTime called");
        QTime currentTime = QTime::currentTime();
        ui->showTime->setText(currentTime.toString("hh:mm:ss"));
        ui->showTime->update();
    }
}

void timer::set_customHMS_visibility(bool visibility)
{
    ui->spinBox_h->setVisible(visibility);
    ui->custom_h_label->setVisible(visibility);
    ui->spinBox_m->setVisible(visibility);
    ui->custom_m_label->setVisible(visibility);
    ui->spinBox_s->setVisible(visibility);
    ui->custom_s_label->setVisible(visibility);
}

void timer::setBackgroundColor(const QColor &color, int millisecs)
{
    if (millisecs == 0) {
        QString styleSheet = QString("background-color: %1;").arg(color.name());
        this->setStyleSheet(styleSheet);
    }
    else {
        QPalette palette = this->palette();
        startColor = palette.color(QPalette::Window);
        qDebug() << "Start color: " << startColor.name();
        endColor = color;
        qDebug() << "End color: " << endColor.name();
        duration = millisecs;
        elapsed = 0;

        colorTimer->start(color_gradient_update_time);
    }
}

void timer::updateBackgroundColor()
{
    if (colorDBG) qDebug("update background called");
    elapsed += color_gradient_update_time;
    if (elapsed >= duration) {
        colorTimer->stop();
        if (colorDBG) qDebug("Color Timer stopped");
        QString styleSheet = QString("background-color: %1;").arg(endColor.name());
        this->setStyleSheet(styleSheet);
        return;
    }

    // interpolate color
    float t = static_cast<float>(elapsed) / duration;
    int r = startColor.red() + t * (endColor.red() - startColor.red());
    int g = startColor.green() + t * (endColor.green() - startColor.green());
    int b = startColor.blue() + t * (endColor.blue() - startColor.blue());
    QColor currentColor(r, g, b);
    if (colorDBG) qDebug() << "Current color: " << currentColor.name();

    // set new background color
    QString styleSheet = QString("background-color: %1;").arg(currentColor.name());
    this->setStyleSheet(styleSheet);
    if (colorDBG) qDebug("Set current color. ");
}


void timer::on_exit_button_clicked()
{
    delete this;
}

