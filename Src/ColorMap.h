#ifndef COLORMAP_H
#define COLORMAP_H

#include <QMap>
#include <QColor>

class ColorMap
{
public:
    QColor getColor(int id) const;
    QColor getColor(QString name) const;
    int getIndex(QColor color) const;
};

#endif // COLORMAP_H
