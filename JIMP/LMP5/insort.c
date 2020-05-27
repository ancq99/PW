#include "insort.h"

void
insort (double v[], int n)
{
  int i, j;
  for (i = 1; i < n; i++) {
	  double tmp = v[i];
  for (j = i-1; v[j] > tmp && j >= 0; j--)
	  v[j+1] = v[j];
  v[j+1] = tmp;
  }
}
