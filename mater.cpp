#include<stdio.h>
#include "mater.h"
#include "constants.h"
/******************************************************************************/
double get_absorption(const double lambda) {
    return 2 * 2 * pi * cspeed / lambda;
}

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
void output_eta_x(int Nx, const double *eta, double dx, const char *tag){
    char fname[100];
    sprintf(fname, "eta_vs_x_%s.dat", tag);
    FILE *fp=fopen(fname, "w");
    fprintf(fp, "# 1: x (micron) | 2 : eta \n");
    for(int i=0; i<Nx; i++){
        double x=i*dx;
        fprintf(fp, "% .12e % .12e\n", 1e-3*x, eta[i]);
    }
    fclose(fp);
    printf("Completed writing to file \"%s\"\n", fname);
}
/******************************************************************************/

void create_slab(int Nx, double *eps, double* eta, int j1, int j2,
                 double eslab, double sigmaslab, double dt){
    /*
     * Creates array of dielectric permittivity
     */
    for(int i=0; i<Nx; i++){
        eps[i] = 1;
        eta[i] = 0;
    }
    for(int i=j1; i<j2+1; i++){
        eps[i] = eslab;
        eta[i] = 2*pi*sigmaslab*dt;
    }
}
/******************************************************************************/
void update_Ey_var1(int Nx,
                    double *Ey, double *EyPrev,
                    const double *Dy, const double *DyPrev,
                    const double *eps, const double* eta){
    /*
     * Calculates E from D, epsilon and eta
     */
    for(int i=0; i<Nx; i++){
        double epsEtaSum = eps[i] + eta[i];
        Ey[i] = (eps[i] - eta[i]) / epsEtaSum * EyPrev[i] +
                (Dy[i] - DyPrev[i]) / epsEtaSum;
        EyPrev[i] = Ey[i];
    }
}

void update_Ey_var2(int Nx,
                    double *Ey, 
                    double *sumEyTimePrev,
                    const double *Dy,
                    const double *eps, const double* eta){
    /*
     * Calculates E from D, epsilon and eta
     */
    for(int i=0; i<Nx; i++){
        Ey[i] = (Dy[i] - 2 * eta[i] * sumEyTimePrev[i]) / (eps[i] + eta[i]);
        sumEyTimePrev[i] += Ey[i];
    }
}
/*** END OF FILE **************************************************************/
