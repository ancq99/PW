#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b);
void swap_srct(Matrix *mat,int a,int b);
int inmax(Matrix *mat,int c);
void del_srct(Matrix *mat,Matrix *b,int x,int w);
int scl_srct(Matrix *mat,Matrix *b,int w); 

#endif

