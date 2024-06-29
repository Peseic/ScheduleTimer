#ifndef WINDOW_TITLES_H
#define WINDOW_TITLES_H

#include <QString>

/*
start_use.cpp
register_page.cpp
log_page.cpp
mainwindow.cpp
choosetime.cpp
set_class.cpp
add_dll.cpp
timer.cpp
timer_popup.cpp
*/

class WindowTitles {
public:
    const QString START_USE_WINDOW_TITLE = "Hi!";
    const QString REGISTER_PAGE_WINDOW_TITLE = "Register";
    const QString LOG_PAGE_WINDOW_TITLE = "Login";
    const QString MAINWINDOW_WINDOW_TITLE = "📅Schedule";
    const QString CHOOSETIME_WINDOW_TITLE = "🗓️Choose Time";
    const QString SET_CLASS_WINDOW_TITLE = "📕Set Class";
    const QString ADD_DLL_WINDOW_TITLE = "📌Add DDL";
    const QString TIMER_WINDOW_TITLE = "🍅Pomodoro Timer";
    const QString TIMER_POPUP_WINDOW_TITLE = "⏰Time's up!";


    static WindowTitles& instance() {
        static WindowTitles instance;
        return instance;
    }

private:
    WindowTitles() = default; // Private constructor to enforce singleton pattern
};

#define Q_GLOBAL_STATIC_CLASS(WindowTitles) (WindowTitles::instance())

#endif // WINDOW_TITLES_H
