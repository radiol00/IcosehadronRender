#include "sphere.h"

Sphere::Sphere()
{
    QPoint P1(50,400);
    QPoint P2(225,50);
    QPoint P3(400,400);
    BT = BitmapTriangle(P1,P2,P3);
    int d = 100;
    QVector<Vertex> Vertices;
    int X = int(floor(.525731112119133606f * d));
    int Z = int(floor(.850650808352039932f * d));
    int N = int(floor(0.f * d));


    Vertex V;
    V = Vertex(-X,N,Z); Vertices.push_back(V);
    V = Vertex(X,N,Z); Vertices.push_back(V);
    V = Vertex(-X,N,-Z); Vertices.push_back(V);
    V = Vertex(X,N,-Z); Vertices.push_back(V);
    V = Vertex(N,Z,X); Vertices.push_back(V);
    V = Vertex(N,Z,-X); Vertices.push_back(V);
    V = Vertex(N,-Z,X); Vertices.push_back(V);
    V = Vertex(N,-Z,-X); Vertices.push_back(V);
    V = Vertex(Z,X,N); Vertices.push_back(V);
    V = Vertex(-Z,X,N); Vertices.push_back(V);
    V = Vertex(Z,-X,N); Vertices.push_back(V);
    V = Vertex(-Z,-X,N); Vertices.push_back(V);

    Triangle T;


    T = Triangle(Vertices[0],Vertices[4],Vertices[1],BT); Triangles.push_back(T);
    T = Triangle(Vertices[0],Vertices[9],Vertices[4],BT); Triangles.push_back(T);
    T = Triangle(Vertices[9],Vertices[5],Vertices[4],BT); Triangles.push_back(T);
    T = Triangle(Vertices[4],Vertices[5],Vertices[8],BT); Triangles.push_back(T);
    T = Triangle(Vertices[4],Vertices[8],Vertices[1],BT); Triangles.push_back(T);

    T = Triangle(Vertices[8],Vertices[10],Vertices[1],BT); Triangles.push_back(T);
    T = Triangle(Vertices[8],Vertices[3],Vertices[10],BT); Triangles.push_back(T);
    T = Triangle(Vertices[5],Vertices[3],Vertices[8],BT); Triangles.push_back(T);
    T = Triangle(Vertices[5],Vertices[2],Vertices[3],BT); Triangles.push_back(T);
    T = Triangle(Vertices[2],Vertices[7],Vertices[3],BT); Triangles.push_back(T);

    T = Triangle(Vertices[7],Vertices[10],Vertices[3],BT); Triangles.push_back(T);
    T = Triangle(Vertices[7],Vertices[6],Vertices[10],BT); Triangles.push_back(T);
    T = Triangle(Vertices[7],Vertices[11],Vertices[6],BT); Triangles.push_back(T);
    T = Triangle(Vertices[11],Vertices[0],Vertices[6],BT); Triangles.push_back(T);
    T = Triangle(Vertices[0],Vertices[1],Vertices[6],BT); Triangles.push_back(T);

    T = Triangle(Vertices[6],Vertices[1],Vertices[10],BT); Triangles.push_back(T);
    T = Triangle(Vertices[9],Vertices[0],Vertices[11],BT); Triangles.push_back(T);
    T = Triangle(Vertices[9],Vertices[11],Vertices[2],BT); Triangles.push_back(T);
    T = Triangle(Vertices[9],Vertices[2],Vertices[5],BT); Triangles.push_back(T);
    T = Triangle(Vertices[7],Vertices[2],Vertices[11],BT); Triangles.push_back(T);
}

int Sphere::getSize()
{
    return Triangles.size();
}

Triangle Sphere::getFace(int i)
{
    return Triangles[i];
}

void Sphere::devide(int i)
{
    for(int o = 0; o < i; o++)
    {
        int size = Triangles.size();

        for(int i = 0; i<size; i++)
        {
            Triangle T = Triangles[0];
            Vertex mid1((T.getV(0).getx() + T.getV(1).getx())/2, (T.getV(0).gety() + T.getV(1).gety())/2, (T.getV(0).getz() + T.getV(1).getz())/2);
            Vertex mid2((T.getV(1).getx() + T.getV(2).getx())/2, (T.getV(1).gety() + T.getV(2).gety())/2, (T.getV(1).getz() + T.getV(2).getz())/2);
            Vertex mid3((T.getV(2).getx() + T.getV(0).getx())/2, (T.getV(2).gety() + T.getV(0).gety())/2, (T.getV(2).getz() + T.getV(0).getz())/2);

            mid1.normalize();
            mid2.normalize();
            mid3.normalize();

            Triangle T1(mid1,mid2,mid3,BT);
            Triangle T2(T.getV(0),mid1,mid3,BT);
            Triangle T3(T.getV(1),mid1,mid2,BT);
            Triangle T4(T.getV(2),mid2,mid3,BT);

            Triangles.push_back(T1);
            Triangles.push_back(T2);
            Triangles.push_back(T3);
            Triangles.push_back(T4);

            Triangles.remove(0);
        }
    }

}

