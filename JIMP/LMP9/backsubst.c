
#include "backsubst.h"
#include <stdio.h>

int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	if(x->r == mat->r)
		{
		int rc=mat->r-1;
		for(int i=0;i<rc+1;i++)
			{
			for(int d=0;d<i;d++)
				b->data[rc-i][0]-=mat->data[rc-i][rc-d]*x->data[d][0];
			if(mat->data[rc-i][rc-i]!=0)
				x->data[i][0]=b->data[rc-i][0]/mat->data[rc-i][rc-i];
			else
				return 1;
			}
		return 0;
		}
	else
		return 2;	
}



