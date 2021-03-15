#ifndef VETOR2_H
#define VETOR2_H
#include <iostream>
using namespace std;

class Vetor2
{
    public:

        double x;
        double y;

        Vetor2();
        Vetor2(double x, double y);
        virtual ~Vetor2();

        Vetor2 operator+(const Vetor2 &v)const;
        Vetor2 operator-(const Vetor2 &v)const;
        Vetor2 operator*(const double &e);
        friend Vetor2 operator*(const double &e,const Vetor2 &v);
        double operator*(const Vetor2 &v)const;
        friend ostream & operator<<(ostream & out, const Vetor2 &v);
        double modulo()const;
        Vetor2 unitario()const;
        Vetor2 proj_v(const Vetor2 &v)const;
        double proj_e(const Vetor2 &v)const;
        Vetor2 comp_ort(const Vetor2 &v)const;



};

#endif // VETOR2_H
//blah
