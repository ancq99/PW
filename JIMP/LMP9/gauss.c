
﻿#include "gauss.h"
			
void swap_srct(Matrix *mat,int a,int b)
{
  double *tmp = mat->data[a];
  mat->data[a] = mat->data[b];
  mat->data[b] = tmp;
}

int scl_srct(Matrix *mat,Matrix *b,int w)
{       
  if( mat->data[w][w] != 0 ){
    double x = 1 / mat->data[w][w];
    int z = mat->c - w;
    for(int i = 0 ; i < z ; i++)
      mat->data[w][w+i] = mat->data[w][w+i] * x;
    b->data[w][0] = b->data[w][0] * x;
    return 0;
  }
  else
    return 1;
}

int inmax(Matrix *mat,int c)
{
  int tmp = 0;
  double max = 0;
  for(int i = 0 ; i < mat->r ; i++ )
    if( mat->data[i][c] > max){
      max = mat->data[i][c];
      tmp = i;
    }
  return tmp;
}

void del_srct(Matrix *mat,Matrix *b,int x,int w)
{
  double k = mat->data[x][w];
  for(int i = 0 ; i < mat->c ; i++ )
    mat->data[x][i] -= mat->data[w][i] * k;
  b->data[x][0] -= b->data[w][0] * k;
}

int eliminate(Matrix *mat, Matrix *b)
{
  for(int i = 0 ; i < mat->c ; i++){
    int max = inmax( mat , i );
    if ( max != 0 ){
      swap_srct( mat , i , max );
      swap_srct( b , i , max );
    }
    if( scl_srct( mat , b , i )!=1 )
      for(int d = i+1 ; d < mat->r ; d++)
	del_srct( mat , b , d , i );
      else
	return 1;
  }
  return 0;
}





