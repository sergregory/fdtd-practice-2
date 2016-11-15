#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
typedef double complex dcomplex;
#include "fdtd_1d_maxwell.h"
#include "pulse.h"
#include "output.h"
#include "mater.h"
#include "set_mem.h"
#include "rfourier.h"
#include "constants.h"
#include <opencv2/highgui.hpp>
/******************************************************************************/
void slab(void){
    char *tag="e_1_var2";
    // used to label output files
    /** Optical pulse ***/
    double lambda0 = 600; // nm
    double tau = 5; // fs, width of the pulse
    /** Slab parameters **/
    double sigmaslab = 0;//get_absorption(lambda0); // absorption of the slab
    double eslab = 1.; //2.0; // permittivity of the slab
    /*** Computational parameters ***/
    double dx = 20.0; // nm
    int Nx = 20000; // number of cells along x
    int ix0 = 9000; // center of the pulse at t=0
    int Nslab = 200; // width of the slab
    int si1 = 10000;// start of the slab
    int si2 = si1+Nslab-1;// end of the slab
    int fi1 = 7500; // location of fourier transform
    int fi2 = si2+10; // location of fourier transform
    double xi = 0.99;
    int No = 200; // defines the output rate
    int Nd = 10; // defines the draw rate
    /*** start execution ***/
    double w0 = 2*pi*cspeed/lambda0; // rad/fs
    double dt = xi*dx/cspeed; // in fs
    printf("dx=%.12e nm, dt=%.12e fs\n", dx, dt);
    /*** arrays for the fields ***/
    double *fields = static_cast<double*>(calloc(6*Nx, sizeof(double)));
    double *Hz = fields+0*Nx;
    double *Ey = fields+1*Nx;
    double *EyPrev = fields+2*Nx;
    double *Dy = fields+3*Nx;
    double *DyPrev = fields+4*Nx;
    double *SumEyTimePrev = fields+5*Nx;
    double *eps = static_cast<double*>(calloc(Nx, sizeof(double)));
    double *eta = static_cast<double*>(calloc(Nx, sizeof(double)));
    create_slab(Nx, eps, eta, si1, si2, eslab, sigmaslab, dt);
    output_eps_x(Nx, eps, dx, tag);
    create_initial_dist(Nx, Dy, Hz, dx, dt, cspeed, ix0, tau, w0);
    update_Ey_var2(Nx, Ey, SumEyTimePrev, Dy, eps, eta);
    output_Ey_vs_x(Nx, Ey, 0, dx, tag);
    output_Hz_vs_x(Nx, Hz, 0, dx, tag);
    draw_Ey_vs_x(Nx, Ey, 0, dx, tag, fi1, fi2);
    draw_Hz_vs_x(Nx, Hz, 0, dx, tag, fi1, fi2);
    int T=0; // total steps
    int keyCode = cv::waitKey(0);
    if (keyCode == 's') {
        printf("Elapsed time -> %g fs (%d steps)\n", dt*(T), T);
        output_Ey_vs_x(Nx, Ey, T, dx, tag);
        output_Hz_vs_x(Nx, Hz, T, dx, tag);
    }
    double wmin = 0.8*w0; // rad/fs
    double wmax = 1.2*w0; // rad/fs
    int Nw=200;
    dcomplex *ftall= static_cast<dcomplex*>(malloc(2*Nw*sizeof(dcomplex)));
    dcomplex *ft1 = ftall + 0*Nw;
    dcomplex *ft2 = ftall + 1*Nw;
    zset_mem(2*Nw, ftall, 0.0+I*0.0); // both parts of complex
    for(;;++T){
        /* printf("Number of steps to run (<=0 to exit) -> "); fflush(stdout); */
        /* int steps; */
        /* scanf("%d", &steps); */
        /* if(steps<=0) break; */
        /* printf("Making %d steps\n", steps); */
        /* for(int n=0; n<steps; n++, T++){ */
        update_Bz(Nx, Hz, Ey, xi);
        // find Bz at n+1/2
        update_Dy(Nx, Dy, DyPrev, Hz, xi);
        // find Dy at n+1
        update_Ey_var2(Nx, Ey, SumEyTimePrev, Dy, eps, eta);
        /* output of Ey */
        if((T+1)%Nd == 0){
            draw_Ey_vs_x(Nx, Ey, 0, dx, tag, fi1, fi2);
            draw_Hz_vs_x(Nx, Hz, 0, dx, tag, fi1, fi2);
            int keyCode = cv::waitKey(0) & 0xFF;
            if (keyCode == 27) //ESC
                break;
            if (keyCode == 's') {
                printf("Elapsed time -> %g fs (%d steps)\n", dt*(T+1), T+1);
                /* output_Ey_vs_x(Nx, Ey, T+1, dx, tag); */
                /* output_Hz_vs_x(Nx, Hz, T+1, dx, tag); */
            }
        }
        /* output of Hz */
        if((T+1)%No == 0){
            printf("Elapsed time -> %g fs (%d steps)\n", dt*(T+1), T+1);
            /* output_Ey_vs_x(Nx, Ey, T+1, dx, tag); */
            /* output_Hz_vs_x(Nx, Hz, T+1, dx, tag); */
        }
        /*** take running fourier ***/
        double time=dt*(T+1); // for Ey
        rfourier2(wmin, wmax, Nw, ft1, ft2, Ey[fi1], Ey[fi2], dt, time);
    }// end of global loop
    char fname1[100], fname2[100];
    sprintf(fname1, "ft_fi=%d_%s.dat", fi1, tag);
    sprintf(fname2, "ft_fi=%d_%s.dat", fi2, tag);
    four_out(Nw, ft1, wmin, wmax, fname1);
    four_out(Nw, ft2, wmin, wmax, fname2);
    free(fields); free(eps); free(ftall);
    free(eta);
}
/*****************************************************************************/
int main(void){
    slab();
    return 0;
}
