#include<stdio.h>
#include<math.h>
#include<complex.h>

#include "constants.h"
#include "rfourier.h"

typedef double complex dcomplex;
/******************************************************************************/
void four_out(int Nw, const dcomplex *ft, double wmin, double wmax,
        const char *fname){
    FILE *fp=fopen(fname, "w");
    printf("output to \"%s\"\n", fname);
    double dw=(wmax-wmin)/(Nw-1.0);
    for(int i=0; i<Nw; i++){
        double w=wmin+dw*i;
        fprintf(fp, "% .12e % .12e % .12e\n", w, creal(ft[i]), cimag(ft[i]));
    }
    fclose(fp);
}
/******************************************************************************/
void rfourier2(double wmin, double wmax, int Nw, dcomplex *ft1, dcomplex *ft2,
        double Ey1, double Ey2, double dt, double time){
    double dw = (wmax-wmin)/(Nw-1.0);
    double mult=dt/(2*pi);
    for(int n=0; n<Nw; n++){
        double w=wmin+dw*n;
        dcomplex ce=mult*cexp(I*w*time);
        ft1[n] += ce*Ey1;
        ft2[n] += ce*Ey2;
    }
}
/*** END OF FILE **************************************************************/
