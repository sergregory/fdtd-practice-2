#pragma once
void update_Ey(int Nx, double *Ey, const double *Dy, const double *ebkg);
void create_slab(int Nx, double *eps, int j1, int j2, double eslab);
void output_eps_x(int Nx, const double *eps, double dx, const char *tag);
