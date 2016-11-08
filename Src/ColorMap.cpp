#include "ColorMap.h"
#include <QObject>

QColor ColorMap::getColor(int id) const
{
    if (id == 1)
    {
        return QColor("white");
    }
    if (id == 2)
    {
        return QColor("red");
    }
    if (id == 3)
    {
        return QColor("yellow");
    }
    if (id == 4)
    {
        return QColor("green");
    }
    if (id == 5)
    {
        return QColor("blue");
    }
    return QColor();
}

QColor ColorMap::getColor(QString name) const
{
    if (name == QObject::tr("Белый"))
    {
        return QColor("white");
    }
    if (name == QObject::tr("Красный"))
    {
        return QColor("red");
    }
    if (name == QObject::tr("Желтый"))
    {
        return QColor("yellow");
    }
    if (name == QObject::tr("Зеленый"))
    {
        return QColor("green");
    }
    if (name == QObject::tr("Синий"))
    {
        return QColor("blue");
    }
    return QColor();
}

int ColorMap::getIndex(QColor color) const
{
    if (color == QColor("white"))
    {
        return 1;
    }
    if (color == QColor("red"))
    {
        return 2;
    }
    if (color == QColor("yellow"))
    {
        return 3;
    }
    if (color == QColor("green"))
    {
        return 4;
    }
    if (color == QColor("blue"))
    {
        return 5;
    }
    return 1;
}
