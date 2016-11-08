#pragma once

void output_Ey_vs_x(int Nx, const double *Ey, int T, double dx, const char *tag);
void output_Hz_vs_x(int Nx, const double *Hz, int T, double dx, const char *tag);
void draw_Ey_vs_x(int Nx, const double *Ey, int T, double dx, const char *tag, int fi1, int fi2);
void draw_Hz_vs_x(int Nx, const double *Hz, int T, double dx, const char *tag, int fi1, int fi2);
