#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calnum.h"

double calnum(double (*f) (double),  double poczatek, double koniec, int ilosc_krokow)
{
        double dx = (koniec - poczatek) / ilosc_krokow;
        double outcome = 0;
        for(int i = 1; i <= ilosc_krokow; i++)
        {
                double xi = poczatek + i * dx;
                outcome += f(xi);
        }
        return outcome * dx;

}

