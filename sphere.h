#ifndef SPHERE_H
#define SPHERE_H

#include "triangle.h"
#include <QVector>
#include <QMap>
#include <QPair>

class Sphere
{
    QVector<Triangle> Triangles;
    BitmapTriangle BT;
public:
    Sphere();
    Triangle getFace(int i);
    void devide(int);
    int getSize();
};

#endif // SPHERE_H
