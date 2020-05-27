#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char ** argv) {
  int res;
  Matrix * A = readFromFile(argc > 1 ? argv[1] : "A" );
  Matrix * b = readFromFile(argc > 2 ? argv[2] : "b" );
  Matrix * x;

  if (A == NULL) return -1;
  if (b == NULL) return -2;
  printToScreen(A);
  printToScreen(b);

  res = eliminate(A,b);
  x = createMatrix(b->r, 1);
  if (x != NULL) {
    res = backsubst(x,A,b);

    printToScreen(x);
    freeMatrix(x);
  } else {
          fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
  }

  freeMatrix(A);
  freeMatrix(b);

  return 0;
}
