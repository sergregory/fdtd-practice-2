#include<stdio.h>
#include<string.h>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

void output_Ey_vs_x(int Nx, const double *Ey, int T, double dx, const char *tag){
    char fname[100];
    sprintf(fname, "Ey_vs_x_T=%d_%s.dat", T, tag);
    FILE *fp=fopen(fname, "w");
    fprintf(fp, "# 1: x (micron) | 2 : Ey (a.u.) \n");
    for(int i=0; i<Nx; i++){
        double x=i*dx;
        fprintf(fp, "% .12e % .12e\n", 1e-3*x, Ey[i]);
    }
    fclose(fp);
    printf("Completed writing to file \"%s\"\n", fname);
}

void output_Hz_vs_x(int Nx, const double *Hz, int T, double dx, const char *tag){
    char fname[100];
    sprintf(fname, "Hz_vs_x_T=%d_%s.dat", T, tag);
    FILE *fp=fopen(fname, "w");
    fprintf(fp, "# 1: x (micron) | 2 : Hz (a.u.) \n");
    for(int i=0; i<Nx; i++){
        double x=i*dx;
        fprintf(fp, "% .12e % .12e\n", 1e-3*x, Hz[i]);
    }
    fclose(fp);
    printf("Completed writing to file \"%s\"\n", fname);
}

void draw_Ey_vs_x(int Nx, const double *Ey, int T, double dx, const char *tag){
    cv::Mat img(400, Nx*dx / 100, CV_8UC1);
    img.setTo(0);
    for(int i=0; i<Nx; i++){
        img.at<uchar>((int)(200 - Ey[i]*100), i*dx / 100) = 255;
    }
    cv::imshow("Ey", img);
}

void draw_Hz_vs_x(int Nx, const double *Hz, int T, double dx, const char *tag){
    cv::Mat img(400, Nx*dx / 100, CV_8UC1);
    img.setTo(0);
    for(int i=0; i<Nx; i++){
        img.at<uchar>((int)(200 - Hz[i]*100), i*dx / 100) = 255;
    }
    cv::imshow("Hz", img);
}
/*** END OF FILE **************************************************************/
