#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define NUMFILES 400

const int N = 501;
const double L = 100.0;
const double T = 40.0;
const double rho = 10.0;
const double c = sqrt(T/rho);
const double c1 = c;
const double ratio = c*c/(c1*c1);

void linspace(double *x,double start,double stop,int n){
    double step = (stop - start)/(double)(n-1);
    for(int i =0; i < n;i++)
        x[i] = i*step;
}

int main(int argc, char const* argv[]){
    FILE *files[NUMFILES];
    
    for(int i = 0; i < NUMFILES; i++){
        char filename[20];
        sprintf( filename, "results%d.dat", i );
        files[i] = fopen(filename, "w");
    }
    
    int i,j;
    double x[N];
    double U[3][N];

    for(i = 1; i < 3;i++){
        for(j = 0; j < N; j++){
            U[i][j] = 0.0;
        }
    }

    linspace(x, 0.0, L, N);
    
    for(i = 0; i < N; i++){
        if( x[i] <= 0.8*L )
            U[0][i] = 1.25*x[i]/L;
        else
            U[0][i] = 5.0 - 5.0*x[i]/L;
    }
    
    for(i = 1; i < N-1; i++) 
        U[1][i] = U[0][i] + 0.5*ratio*(U[0][i+1] + U[0][i-1] - 2.0*U[0][i]);
    
    int k = 0;
    for(double t = 0; t < 200; t+= 0.5){
        for(i = 1;i < N-1; i++) 
            U[2][i] = 2.0*U[1][i] - U[0][i] + ratio*(U[1][i+1] + U[1][i-1] - 2*U[1][i]);

        for(i = 0; i < N; i++) 
            fprintf( files[k], "%f\t%f\n", x[i], U[2][i] );
        k += 1;

        for(i = 0; i < N; i++){
            U[0][i] = U[1][i];
            U[1][i] = U[2][i];
        }
    }
    
    return 0;
}
