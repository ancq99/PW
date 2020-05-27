#ifndef _BIBL_H_           
#define _BIBL_H_

#include <stdio.h>

int             read(FILE * p, double v[], int max_l_e);

double           L2(double v[], int n);

double           dot_product(double v[], double u[], int n);

double norma_max(double v[], int n);

void mnozenie_przez_liczbe(double *v, int n, int mnoznik);

void dodawanie_wektorow(double *v, double *u, int dl1, int dl2);

void normalizacja(double *v, int n, double l2);

int save(FILE * s, double v[], int max_l_e);

#endif
