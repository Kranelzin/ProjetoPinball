#include "Vetor2.h"
#include <iostream>
#include <cmath>
using namespace std;

Vetor2::Vetor2():
    x(0),y(0)
{
    //ctor
}
Vetor2::Vetor2(double x, double y):
    x(x),y(y)
{

}

Vetor2::~Vetor2()
{
    //dtor
}

Vetor2 Vetor2::operator+(const Vetor2 &v) const{

    Vetor2 r;
    r.x = x + v.x;
    r.y = y + v.y;

    return r;
}

Vetor2 Vetor2::operator-(const Vetor2 &v) const{

    Vetor2 r;
    r.x = x - v.x;
    r.y = y - v.y;

    return r;
}

Vetor2 Vetor2::operator*(const double &e){

    Vetor2 r;
    r.x = x * e;
    r.y = y * e;

    return r;

}

Vetor2 operator*(const double &e,const Vetor2 &v){

    Vetor2 r;
    r.x = v.x * e;
    r.y = v.y * e;

    return r;
}

double Vetor2::operator*(const Vetor2 &v)const{
    return x*v.x + y*v.y;
}

double Vetor2::modulo()const{
    return  pow ((x*x)+(y*y),0.5);
}

Vetor2 Vetor2::unitario()const{
    Vetor2 r(x,y);
    return r*(1/modulo());
}

Vetor2 Vetor2::proj_v(const Vetor2 &v)const{
     //((produto escalar deste com outro)/(produto escalar outro com outro))*(outro vetor)
    return (((*this)*v)/(v*v))*v;
}


double Vetor2::proj_e(const Vetor2 &v)const{
    return ((*this)*v)*(1/v.modulo());
}
Vetor2 Vetor2::comp_ort(const Vetor2 &v)const{
    return *this - proj_v(v);
}

ostream & operator<<(ostream & out, const Vetor2 &v){
    out << "(" << v.x << "," << v.y << ")";
    return out;
}
