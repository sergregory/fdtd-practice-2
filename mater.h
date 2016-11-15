#pragma once
void update_Ey_var1(int Nx,
                    double *Ey, double *EyPrev,
                    const double *Dy, const double *DyPrev,
                    const double *eps, const double* eta);
void update_Ey_var2(int Nx,
                    double *Ey, 
                    double *sumEyTimePrev,
                    const double *Dy,
                    const double *eps, const double* eta);
void create_slab(int Nx, double *eps, double* eta, int j1, int j2,
                 double eslab, double sigmaslab, double dt);
void output_eps_x(int Nx, const double *eps, double dx, const char *tag);
void output_eta_x(int Nx, const double *eta, double dx, const char *tag);
double get_absorption(const double lambda) ;
