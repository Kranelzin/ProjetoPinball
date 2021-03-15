#ifndef LINE_H
#define LINE_H
#include "Vetor2.h"


class Line
{
    private:
        Vetor2 l0;
        Vetor2 d;


    public:
        Line(double x0,double y0,double x1, double y1);
        virtual ~Line();

        double distancia(double x,double y);


};

#endif // LINE_H
