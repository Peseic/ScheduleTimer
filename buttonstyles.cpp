#include "buttonstyles.h"

QString generateButtonQSS(const QColor& bgColor) {
    return QString(
               "QPushButton {"
               "   background-color: %1; /* variable */"
               "   color: #000000; "
               "   border: 1px solid %2; /* variable, depends on background color */"
               "   border-radius: 5px; "
               "   padding: 5px; "
               "   font: bold 14px;"
               "   font-family: 'Arial', '华文中宋'; "
               "}\n"
               "QPushButton:hover { "
               "   background-color: %3; /* variable, depends on background color. should be more vibrant */"
               "   color: #FFFFFF; "
               "}\n"
               "QPushButton:pressed { "
               "   background-color: %4; /* variable, depends on background color. should be darker than 'hover' color */"
               "   color: #FFFFFF; "
               "}\n"
               ).arg(bgColor.name(), adjustColorBrightness(bgColor, 20), adjustColorBrightness(bgColor, -20));
}

QString adjustColorBrightness(const QColor& color, int delta) {
    QColor adjustedColor = color.lighter(delta); // Example adjustment, can be customized
    return adjustedColor.name();
}
