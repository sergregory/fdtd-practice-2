#include<complex.h>
#include "set_mem.h"
typedef double complex dcomplex;
/******************************************************************************/
void zset_mem(int N, dcomplex *A, dcomplex var){
    for(int i=0; i<N; i++){
        A[i]=var;
    }
}
/******************************************************************************/
void dset_mem(int N, double *A, double var){
    for(int i=0; i<N; i++){
        A[i]=var;
    }
}
/*** END OF FILE **************************************************************/
