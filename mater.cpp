#include<stdio.h>
#include "mater.h"
/******************************************************************************/
void output_eps_x(int Nx, const double *eps, double dx, const char *tag){
    char fname[100];
    sprintf(fname, "eps_vs_x_%s.dat", tag);
    FILE *fp=fopen(fname, "w");
    fprintf(fp, "# 1: x (micron) | 2 : eps \n");
    for(int i=0; i<Nx; i++){
        double x=i*dx;
        fprintf(fp, "% .12e % .12e\n", 1e-3*x, eps[i]);
    }
    fclose(fp);
    printf("Completed writing to file \"%s\"\n", fname);
}
/******************************************************************************/

void create_slab(int Nx, double *eps, int j1, int j2, double eslab){
    /*
     * Creates array of dielectric permittivity
     */
    for(int i=0; i<Nx; i++){
        eps[i] = 1;
    }
    for(int i=j1; i<j2+1; i++){
        eps[i] = eslab;
    }
}
/******************************************************************************/
void update_Ey(int Nx, double *Ey, const double *Dy, const double *eps){
    /*
     * Calculates E from D and epsilon
     */
    for(int i=0; i<Nx; i++){
        Ey[i] = Dy[i]/eps[i];
    }
}
/*** END OF FILE **************************************************************/
