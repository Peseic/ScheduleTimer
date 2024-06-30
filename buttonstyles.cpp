#include "buttonstyles.h"

QString generateButtonQSS(const QColor& bgColor) {
    QColor borderColor = generateBorderColor(bgColor);
    QColor hoverColor = generateHoverColor(bgColor);
    QColor pressedColor = generatePressedColor(bgColor);
    return QString(
               "QPushButton {"
               "   background-color: %1; /* given color. Usually very light */"
               "   color: #000000; "
               "   border: 1px solid %2; /* variable, should be same hue as background color but almost black */"
               "   border-radius: 5px; "
               "   padding: 5px; "
               "   font: bold 14px;"
               "   font-family: 'Arial', '华文中宋'; "
               "}\n"
               "QPushButton:hover { "
               "   background-color: %3; /* variable, depends on background color. should be more vibrant */"
               "   color: #800000; "
               "}\n"
               "QPushButton:pressed { "
               "   background-color: %4; /* variable, depends on background color. should be darker than 'hover' color */"
               "   color: #800000; "
               "}\n"
               ).arg(bgColor.name(), borderColor.name(), hoverColor.name(), pressedColor.name());
}

QColor generateBorderColor(const QColor& bgColor) {
    QColor borderColor = bgColor;
    borderColor.setHsv(bgColor.hue(), 255, 51); // Saturation 100%, Value 20%
    return borderColor;
}

QColor generateHoverColor(const QColor& bgColor) {
    QColor hoverColor = bgColor;
    int newSaturation = qMin(bgColor.saturation() + 50, 255); // Increase saturation
    int newValue = qMin(bgColor.value() + 50, 255); // Increase value
    hoverColor.setHsv(bgColor.hue(), newSaturation, newValue);
    return hoverColor;
}

QColor generatePressedColor(const QColor& bgColor) {
    QColor pressedColor = bgColor;
    int newSaturation = qMin(bgColor.saturation() + 30, 255); // Increase saturation
    int newValue = qMax(bgColor.value() - 30, 0); // Decrease value
    pressedColor.setHsv(bgColor.hue(), newSaturation, newValue);
    return pressedColor;
}
