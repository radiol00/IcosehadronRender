#include "triangle.h"

Triangle::Triangle(Vertex V1, Vertex V2, Vertex V3, BitmapTriangle b)
{
    V[0] = V1;
    V[1] = V2;
    V[2] = V3;
    BT = b;
}

Triangle::Triangle()
{
    QPoint P1(0,0);
    QPoint P2(0,0);
    QPoint P3(0,0);
    V[0] = Vertex(0,0,0);
    V[1] = Vertex(0,0,0);
    V[2] = Vertex(0,0,0);
    BT = BitmapTriangle(P1,P2,P3);
}

Vertex Triangle::getV(int i)
{
    return V[i];
}

QVector3D Triangle::getN(int i)
{
    return Normals[i];
}

void Triangle::calcNormals()
{
    QVector3D A,B;

    A = QVector3D( V[1].getx() - V[0].getx(), V[1].gety() - V[0].gety(), V[1].getz() - V[0].getz());
    B = QVector3D( V[2].getx() - V[0].getx(), V[2].gety() - V[0].gety(), V[2].getz() - V[0].getz());

    Normals[0] = QVector3D::normal(A,B);

    A = QVector3D( V[0].getx() - V[1].getx(), V[0].gety() - V[1].gety(), V[0].getz() - V[1].getz());
    B = QVector3D( V[2].getx() - V[1].getx(), V[2].gety() - V[1].gety(), V[2].getz() - V[1].getz());

    Normals[1] = QVector3D::normal(A,B);

    A = QVector3D( V[1].getx() - V[2].getx(), V[1].gety() - V[2].gety(), V[1].getz() - V[2].getz());
    B = QVector3D( V[0].getx() - V[2].getx(), V[0].gety() - V[2].gety(), V[0].getz() - V[2].getz());

    Normals[2] = QVector3D::normal(A,B);
}

void Triangle::corrNormal(int i)
{
    Normals[i]*=-1;
}

BitmapTriangle Triangle::getBT()
{
    return BT;
}


Triangle Triangle::perspective()
{     
    int d = 1000;

    double V0x = V[0].getx();
    double V0y = V[0].gety();
    double V0z = V[0].getz();

    double V1x = V[1].getx();
    double V1y = V[1].gety();
    double V1z = V[1].getz();

    double V2x = V[2].getx();
    double V2y = V[2].gety();
    double V2z = V[2].getz();


    Vertex vm0(int(floor(d*V0x/V0z+250)),int(floor(-d*V0y/V0z+250)),int(floor(V0z)));
    Vertex vm1(int(floor(d*V1x/V1z+250)),int(floor(-d*V1y/V1z+250)),int(floor(V1z)));
    Vertex vm2(int(floor(d*V2x/V2z+250)),int(floor(-d*V2y/V2z+250)),int(floor(V2z)));

    Triangle T(vm0,vm1,vm2,BT);

    return T;
}

Triangle Triangle::transform(Vertex T,Vertex S,Vertex Sh,Vertex R)
{
    Vertex X[3];
    for (int i = 0; i < 3; i++)
    {
        X[i] = V[i].rotate(R).scale(S).sheare(Sh).translate(T);
    }

    Triangle Tri(X[0],X[1],X[2],BT);
    return Tri;
}
