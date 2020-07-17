#include "canvas.h"
#include <QVector>
#include <QVector3D>
#include <cmath>
#include <QPair>
#include "matrix.h"
#include "sphere.h"


#define ZBUFFER_MAX 999999999
#define PRZESUNIECIE_Z 1500

Canvas::Canvas(QWidget *parent) : QWidget(parent), texture("C:/Users/Tobiasz/Desktop/Projekt 3D/sproboj.png"), background("C:/Users/Tobiasz/Desktop/Projekt 3D/pomarancza.png")
{
    texture = texture.convertToFormat(QImage::Format_RGB888);
    background = background.convertToFormat(QImage::Format_RGB888);
    Translacja.setz(PRZESUNIECIE_Z);

    imW = 500;
    imH = 500;

    for(int i=0;i<500;i++)
        for(int j=0;j<500;j++)
            zBuffer[i][j] = ZBUFFER_MAX;

    Sphere s;
    s.devide(0);


    int size = s.getSize();
    for(int i = 0; i<size; i++)
    {
        Triangles.push_back(s.getFace(i));
    }

// ŚCIANA DLA PRZYKŁADU
//    Vertex p1(250,-250,250);
//    Vertex p2(-250,-250,-250);
//    Vertex p3(250,-250,-250);

//    QPoint P1(50,50);
//    QPoint P2(50,450);
//    QPoint P3(450,450);
//    BitmapTriangle BT = BitmapTriangle(P1,P2,P3);
//    Triangle T(p1,p2,p3,BT);

//    Triangles.push_back(T);

//    p1 = Vertex(250,-250,250);
//    p2 = Vertex(-250,-250,-250);
//    p3 = Vertex(-250,-250,250);

//    T = Triangle(p1,p2,p3,BT);

//    Triangles.push_back(T);

    drawWalls();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.drawImage(0,0,im);

}

void Canvas::putPixel(int x,int y,RGB rgb)
{
    if (x>=0 && x<im.width() && y>=0 && y<im.height())
    {
        unsigned char *line;
        line = im.scanLine(y);
        line[3*x] = rgb.r;
        line[3*x+1] = rgb.g;
        line[3*x+2] = rgb.b;

        update();
    }
    else return;
}

bool Canvas::DoesRayIntersect(Vertex rayOrigin, QVector3D rayVector)
{
    float EPSILON = 0.000001;

    float t;
    int size = TransformedTriangles.size();
    for(int i=0; i<size; i++)
    {
            Vertex V0 = TransformedTriangles[i].getV(0);
            Vertex V1 = TransformedTriangles[i].getV(1);
            Vertex V2 = TransformedTriangles[i].getV(2);

            QVector3D edge1, edge2, h, q, s;
            float a,f,u,v;

            edge1 = QVector3D(V1.getx() - V0.getx(),V1.gety() - V0.gety(), V1.getz() - V0.getz());
            edge2 = QVector3D(V2.getx() - V0.getx(),V2.gety() - V0.gety(), V2.getz() - V0.getz());

            h = QVector3D::crossProduct(rayVector,edge2);
            a = QVector3D::dotProduct(edge1,h);

            if (a < -EPSILON || a > EPSILON){

                f = 1.0/a;
                s = QVector3D(rayOrigin.getx() - V0.getx(), rayOrigin.gety() - V0.gety(), rayOrigin.getz() - V0.getz());
                u = f * QVector3D::dotProduct(s,h);

                if (u >= 0.0 && u <= 1.0){

                    q = QVector3D::crossProduct(s,edge1);
                    v = f * QVector3D::dotProduct(rayVector,q);

                    if (v >= 0.0 && (u + v) <= 1.0) {

                          t = f * QVector3D::dotProduct(edge2,q);
                        if (t > EPSILON) return true;
                        else return false;
                    }
                }
            }
    }
    return false;
}

bool sortujPrzeciecia(QPoint &p1, QPoint &p2)
{
    return p1.x() < p2.x();
}

void Canvas::ScanLine(Triangle triangle, Vertex light)
{
    RGB rgb;

    triangle.calcNormals();

    //Szukanie przedziału Y
    int ymin = triangle.getV(0).gety(), ymax = ymin;
    for(int i=1; i<3; i++)
    {
       int y = triangle.getV(i).gety();
       if(y < ymin) ymin = y;
       if(y > ymax) ymax = y;
    }

    //Szukanie przecięć w przedziale od ymin do ymax
    QList<QPoint> przeciecia;
    for(int y=ymin; y<=ymax; y++)
    {
          if (y<0 && y>=imH) continue;
          przeciecia.clear();
          for(int i=0; i<3; i++)
          {
              int j = (i+1)%3;

              int yi = triangle.getV(i).gety();
              int yj = triangle.getV(j).gety();

              //Czy przecina którąś prostą?
              if((yi <= y && yj > y) || (yi > y && yj <= y))
              {
                  int xi = triangle.getV(i).getx();
                  int xj = triangle.getV(j).getx();
                  int x = int(xi + ((double(xj - xi))/(yj - yi)) * (y - yi));
                  if (x>=imW) x = imW-1;
                  if (x<0) x = 0;
                  QPoint cut(x,y);
                  przeciecia.push_back(cut);
              }
           }


              std::sort(przeciecia.begin(), przeciecia.end(), sortujPrzeciecia);
              for(int i=0;i<przeciecia.size()-1;i+=2)
              {
                  int pocz,kon;
                  int x1=przeciecia[i].x();
                  int x2=przeciecia[i+1].x();
                  if(x1<x2) {
                      pocz = x1;
                      kon = x2;
                  }
                  else {
                      pocz = x2;
                      kon = x1;
                  }


                  for(int x = pocz+1; x<=kon; x++)
                  {
                     if (x<0 && x>=imW) continue;

                      int Mx0 = triangle.getV(0).getx();
                      int My0 = triangle.getV(0).gety();

                      int Mx1 = triangle.getV(1).getx();
                      int My1 = triangle.getV(1).gety();

                      int Mx2 = triangle.getV(2).getx();
                      int My2 = triangle.getV(2).gety();

                      double l1 = ((x - Mx0)*(My2-My0))-((y - My0)*(Mx2 - Mx0));
                      double l2 = ((Mx1 - Mx0)*(y - My0))-((My1-My0)*(x-Mx0));
                      double m = ((Mx1 - Mx0)*(My2-My0))-((My1-My0)*(Mx2-Mx0));

                      double v = l1/m;
                      double w = l2/m;
                      double u = 1.0 - v - w;

                      int z = u * triangle.getV(0).getz() + v * triangle.getV(1).getz() + w * triangle.getV(2).getz();

                      if (z<0) continue;

                      if(zBuffer[x][y]>z)
                      {
                          zBuffer[x][y] = z;
                          QVector3D Normal = -1 * u * triangle.getN(0) + v * triangle.getN(1) + w * triangle.getN(2);

                          QVector3D LightRay(light.getx() - x,light.gety() - y, light.getz() - z);

                          rgb = RGB();

                          float cos = QVector3D::dotProduct(Normal,LightRay)/LightRay.length();
                          cos*= cos < 0 ? -1: 1;

                          rgb = getTexture(u,v,w,triangle.getBT());
                          rgb.r*=cos;
                          rgb.g*=cos;
                          rgb.b*=cos;

                          putPixel(x,y,rgb);
                      }

                   }

              }
    }
}

Canvas::RGB Canvas::getTexture(double u, double v, double w, BitmapTriangle BT)
{
    double x,y;
    RGB color, P1,P2,P3,P4;

    x = u*BT.getPoint(0).x()+v*BT.getPoint(1).x()+w*BT.getPoint(2).x();
    y = u*BT.getPoint(0).y()+v*BT.getPoint(1).y()+w*BT.getPoint(2).y();
    if (x>=0 && x<texture.width() && y>=0 && y<texture.height())
    {

        double a = x - floor(x);
        double b = y - floor(y);
        double a1 = 1.0 - a;
        double b1 = 1.0 - b;


        P1 = getRGB(int(floor(x)),int(ceil(y)));
        P2 = getRGB(int(ceil(x)),int(ceil(y)));
        P3 = getRGB(int(ceil(x)),int(floor(y)));
        P4 = getRGB(int(floor(x)),int(floor(y)));

        color.r = b * (a1 * P1.r + a * P2.r) + b1 * ( a1 * P4.r + a * P3.r);
        color.g = b * (a1 * P1.g + a * P2.g) + b1 * ( a1 * P4.g + a * P3.g);
        color.b = b * (a1 * P1.b + a * P2.b) + b1 * ( a1 * P4.b + a * P3.b);
    }

    return color;
}

Canvas::RGB Canvas::getRGB(int x, int y)
{
    RGB rgb;
    if (x>=0 && x<texture.width() && y>=0 && y<texture.height())
    {
        unsigned char *line;
        line = texture.scanLine(y);

        rgb.r = line[3*x];
        rgb.g = line[3*x+1];
        rgb.b = line[3*x+2];
    }
    return rgb;
}

void Canvas::rayTracing(Vertex light, int x, int y)
{
    if (zBuffer[x][y]==ZBUFFER_MAX) return;

    Vertex Origin(x,y,zBuffer[x][y]);
    QVector3D LightRay(light.getx() - x,light.gety() - y, light.getz() - zBuffer[x][y]);

    if (DoesRayIntersect(Origin,LightRay))
    {
        unsigned char *line;
        line = im.scanLine(y);

        line[3*x] = 0;
        line[3*x+1] = 0;
        line[3*x+2] = 0;
    }

    return;
}

void Canvas::drawWalls()
{
    im = background;

    for(int i=0;i<500;i++)
        for(int j=0;j<500;j++)
            zBuffer[i][j] = ZBUFFER_MAX;

    Vertex Light(250,-1000,0);

    TransformedTriangles.clear();
    int size = Triangles.size();

    for(int i = 0; i<size; i++)
    {
        TransformedTriangles.push_back(Triangles[i].transform(Translacja,Skalowanie,Pochylenie,Obrot).perspective());
        ScanLine(TransformedTriangles[i],Light);
    }


    for(int x = 0; x<imW; x++)
    {
        for(int y = 0; y<imH; y++)
        {
            rayTracing(Light,x,y);
        }
    }

    update();
}

void Canvas::transXChanged(int x)
{
    Translacja.setx(x);
    drawWalls();
}

void Canvas::transYChanged(int y)
{
    Translacja.sety(y);
    drawWalls();
}

void Canvas::transZChanged(int z)
{
    z+=PRZESUNIECIE_Z;
    Translacja.setz(z);
    drawWalls();
}

void Canvas::scaleXChanged(int x)
{
    Skalowanie.setx(x);
    drawWalls();
}

void Canvas::scaleYChanged(int y)
{
    Skalowanie.sety(-y);
    drawWalls();
}

void Canvas::scaleZChanged(int z)
{
    Skalowanie.setz(z);
    drawWalls();
}

void Canvas::tiltXChanged(int H)
{
    Pochylenie.setx(H);
    drawWalls();
}

void Canvas::tiltYChanged(int H)
{
    Pochylenie.sety(H);
    drawWalls();
}

void Canvas::tiltZChanged(int H)
{
    Pochylenie.setz(H);
    drawWalls();
}

void Canvas::rotateXChanged(int a)
{
    Obrot.setx(a);

    drawWalls();
}

void Canvas::rotateYChanged(int a)
{
    Obrot.sety(a);

    drawWalls();
}

void Canvas::rotateZChanged(int a)
{
    Obrot.setz(a);


    drawWalls();
}

