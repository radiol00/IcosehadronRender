#ifndef VERTEXMATRIX_H
#define VERTEXMATRIX_H

#include "matrix.h"
#include <cmath>

class Vertex
{
private:
    int x;
    int y;
    int z;
public:
    Vertex(int,int,int);
    Vertex();
    int getx();
    int gety();
    int getz();
    void setx(int);
    void sety(int);
    void setz(int);
    void normalize();
    Vertex translate(Vertex);
    Vertex scale(Vertex);
    Vertex sheare(Vertex);
    Vertex rotate(Vertex);
};

#endif // VERTEXMATRIX_H
