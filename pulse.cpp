#include<stdio.h>
#include<math.h>

/******************************************************************************/
double pulse(double x, double t, double speed, double tau, double w0){
    double t1 = t - x/speed;
    double a = t1/tau;
    return exp(-a*a)*cos(w0*t1);
}

/******************************************************************************/
void create_initial_dist(int Nx, double *Ey, double *Hz, double dx, double dt,
        double speed, int ix0, double tau, double w0){
    /*
     * Creates Ey[T=0] and Hz[T=-0.5]
     */
    printf("Pulse parameters: w0=%g rad/fs, tau=%g fs\n", w0, tau);
    for(int i=0; i<Nx; i++){
        Ey[i] = pulse(dx*(i+0.0-ix0), 0*dt, speed, tau, w0);
        Hz[i] = pulse(dx*(i+0.5-ix0), -0.5*dt, speed, tau, w0);
    }
    Ey[0]=0; // to satisfy b.c.
}
/*** END OF FILE **************************************************************/
