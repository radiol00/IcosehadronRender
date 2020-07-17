#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "bitmaptriangle.h"
#include "vertex.h"
#include <QVector3D>
#include <cmath>

class Triangle
{
    Vertex V[3];
    BitmapTriangle BT;
    QVector3D Normals[3];
public:
    Triangle(Vertex m1, Vertex m2, Vertex m3, BitmapTriangle BT);
    Triangle();
    Vertex getV(int i);
    QVector3D getN(int i);
    void calcNormals();
    void corrNormal(int i);
    BitmapTriangle getBT();
    Triangle perspective();
    Triangle transform(Vertex,Vertex,Vertex,Vertex);
};

#endif // TRIANGLE_H
