#include "vertex.h"

Vertex::Vertex(int xv, int yv, int zv)
{
   x = xv;
   y = yv;
   z = zv;
}

Vertex::Vertex()
{
   x = 0;
   y = 0;
   z = 0;
}

int Vertex::getx()
{
    return x;
}

int Vertex::gety()
{
    return y;
}

int Vertex::getz()
{
    return z;
}

void Vertex::setx(int xv)
{
    x = xv;
}

void Vertex::sety(int yv)
{
    y = yv;
}

void Vertex::setz(int zv)
{
    z = zv;
}

void Vertex::normalize()
{
    double length = sqrt(x*x+y*y+z*z)/100;
    x/=length;
    y/=length;
    z/=length;
}

Vertex Vertex::translate(Vertex T)
{
    Vertex X(x+T.getx(),y+T.gety(),z+T.getz());
    return X;
}

Vertex Vertex::scale(Vertex S)
{
    double sX = pow(2,S.getx());
    double sY = pow(2,S.gety());
    double sZ = pow(2,S.getz());
    Vertex X(int(floor(x*sX)),int(floor(y*sY)),int(floor(z*sZ)));
    return X;
}

Vertex Vertex::sheare(Vertex S)
{
    Vertex X(x + y*S.gety()/100. + z*S.getz()/100.,x*S.getx()/100. + y + z*S.getz()/100.,x*S.getx()/100. + y*S.gety()/100. + z);
    return X;
}

Vertex Vertex::rotate(Vertex R)
{
    double ax = (R.getx()*M_PI/180.);
    double ay = (R.gety()*M_PI/180.);
    double az = (R.getz()*M_PI/180.);
    Vertex X;
    Vertex Xp(x,y,z);

    X.setx(Xp.getx());
    X.sety(Xp.gety() * cos(ax) - Xp.getz() * sin(ax));
    X.setz(Xp.gety() * sin(ax) + Xp.getz() * cos(ax));

    Xp = Vertex(X.getx(),X.gety(),X.getz());

    X.setx(Xp.getx()*cos(ay) + Xp.getz()*sin(ay));
    X.sety(Xp.gety());
    X.setz(-1*Xp.getx()*sin(ay) + Xp.getz()*cos(ay));

    Xp = Vertex(X.getx(),X.gety(),X.getz());

    X.setx(Xp.getx()*cos(az) - Xp.gety()*sin(az));
    X.sety(Xp.getx()*sin(az) + Xp.gety()*cos(az));
    X.setz(Xp.getz());

    return X;
}


