#ifndef BUTTONSTYLES_H
#define BUTTONSTYLES_H

#include <QString>
#include <QColor>

QString generateButtonQSS(const QColor& bgColor);
QString adjustColorBrightness(const QColor& color, int delta);

#endif // BUTTONSTYLES_H
