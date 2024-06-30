#ifndef BUTTONSTYLES_H
#define BUTTONSTYLES_H

#include <QString>
#include <QColor>

QString generateButtonQSS(const QColor& bgColor);

QColor generateBorderColor(const QColor& bgColor);
QColor generateHoverColor(const QColor& bgColor);
QColor generatePressedColor(const QColor& bgColor);

#endif // BUTTONSTYLES_H
