#include "Line.h"

Line::Line(double x0,double y0,double x1, double y1):
    l0(x0,y0),d(x1-x0,y1-y0)
{
    //ctor
}


Line::~Line()
{
    //dtor
}

double Line::distancia(double x,double y){
    Vetor2 p(x-l0.x,y-l0.y);
    Vetor2 comp_orto = p.comp_ort(d);
    return comp_orto.modulo();
}

/*
A posição final r = l0 + t*d
r = l0 + t*d =>
r_x = l0_x + t*d_x & r_y = l0_y + t*d_y

r_x = l0_x + t1*d_x => t1 = (r_x - l0_x)/d_x
r_y = l0_y + t2*d_y => t2 = (r_y - l0_y)/d_y


se o ponto ta na linha existe um t tal que

p = l0 + k * d
t1 = t2

Se o ponto pertence ao seguimento imploca que

0<= t <=1

*/
