#ifndef BITMAPTRIANGLE_H
#define BITMAPTRIANGLE_H

#include <QPoint>

class BitmapTriangle
{
    QPoint P[3];
public:
    BitmapTriangle();
    BitmapTriangle(QPoint,QPoint,QPoint);
    QPoint getPoint(int);
};

#endif // BITMAPTRIANGLE_H
