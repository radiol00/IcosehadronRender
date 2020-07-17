#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <cmath>
#include "matrix.h"
#include "triangle.h"
#include "vertex.h"

class Canvas : public QWidget
{
    struct RGB
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;

        RGB():r(0),g(0),b(0){}
        RGB(unsigned char red, unsigned char green, unsigned char blue):r(red),g(green),b(blue){}
    };

    Vertex Translacja;
    Vertex Skalowanie;
    Vertex Pochylenie;
    Vertex Obrot;
    QList<Triangle> Triangles;
    QVector<Triangle> TransformedTriangles;
    QVector<Triangle> Environment;
    QImage im;
    QImage texture;
    QImage background;
    int imW;
    int imH;

    int zBuffer[500][500];
    Q_OBJECT

private:
    void paintEvent(QPaintEvent *event);
    void ScanLine(Triangle,Vertex);
    RGB getTexture(double,double,double,BitmapTriangle);
    RGB getRGB(int,int);
    void putPixel(int,int,RGB);
    bool DoesRayIntersect(Vertex,QVector3D);
    void rayTracing(Vertex,int,int);
    void drawWalls();
public:
    explicit Canvas(QWidget *parent = nullptr);

signals:
public slots:
    void transXChanged(int);
    void transYChanged(int);
    void transZChanged(int);

    void scaleXChanged(int);
    void scaleYChanged(int);
    void scaleZChanged(int);

    void tiltXChanged(int);
    void tiltYChanged(int);
    void tiltZChanged(int);

    void rotateXChanged(int);
    void rotateYChanged(int);
    void rotateZChanged(int);
};

#endif // CANVAS_H
