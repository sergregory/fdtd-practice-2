/******************************************************************************/
void update_Bz(int Nx, double *Bz, const double *Ey, double xi){
    for(int i=0; i<Nx-1; i++){// except the last point
        Bz[i] +=-xi*(Ey[i+1]-Ey[i]);
    }
    int i=Nx-1; // last point
    Bz[i] +=-xi*(0.0 - Ey[i]);
}

/******************************************************************************/
void update_Dy(int Nx, double *Dy, const double *Hz, double xi){

    // Ey[0]=0 always and not updated    
    for(int i=1; i < Nx; i++){
        Dy[i] +=-xi*(Hz[i]-Hz[i-1]);
    }
}
/*** END OF FILE **************************************************************/
