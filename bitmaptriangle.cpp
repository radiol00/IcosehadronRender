#include "bitmaptriangle.h"

#include <QPoint>

BitmapTriangle::BitmapTriangle()
{
    P[0].setX(0);
    P[0].setY(0);

    P[1].setX(0);
    P[1].setY(0);

    P[2].setX(0);
    P[2].setY(0);
}

BitmapTriangle::BitmapTriangle(QPoint p1, QPoint p2, QPoint p3)
{
    P[0]=p1;
    P[1]=p2;
    P[2]=p3;
}

QPoint BitmapTriangle::getPoint(int i)
{
    return P[i];
}
