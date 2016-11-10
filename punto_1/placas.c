#include <stdlib.h>
#include <math.h>
#include <stdio.h>

const double L = 5.0;
const double l = 2.0;
const double h = 0.02;
const double d = 1.0;
const double V0 = 100.0;

#define N (int)(L/h)
#define D (int)(d/h)
#define LL (int)(l/h)

void init_matrix( double m[N][N] );
void boundary_conditions( double m[N][N] );
void relaxation_step( double m[N][N] );
void compute_E( double m[N][N], double Ex[N][N], double Ey[N][N] );
void write( FILE*, double mat[N][N] );

int main(){
    FILE *Potential, *FieldEx, *FieldEy;
    Potential = fopen("potential.dat","w");
    FieldEx = fopen("FieldEx.dat","w");
    FieldEy = fopen("FieldEy.dat","w");
    
    double U[N][N];
    double Ex[N][N];
    double Ey[N][N];
    
    init_matrix( U );
    
    for(int n=0; n<= 2*N*N; n++){
        boundary_conditions( U );
        relaxation_step( U );
    }
    
    compute_E( U, Ex, Ey );
    write( Potential, U ); 
    write( FieldEx, Ex ); 
    write( FieldEy, Ey ); 
    
    fclose(Potential);
    fclose(FieldEx);
    fclose(FieldEy);
    return 0;
}

void init_matrix(double m[N][N]){
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            m[i][j] = 0.0;
}

void boundary_conditions(double mat[N][N]){
    int cond1, cond2, bl, br;
    
    cond1 = (int)( N/2 - D/2 -1);
    cond2 = (int)( N/2 + D/2 - 1);
    bl = (int)( N/2 - LL/2 - 1);
    br = (int)( N/2 + LL/2 - 1);
     
    // condiciones sobre las placas de los condensadores
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if( i == cond1 && j >= bl && j<= br ){
                mat[i][j] = -V0/2;
            } else if( i == cond2 && j >= bl && j<= br ){
                mat[i][j] = V0/2;
            }
        }
    }
    
    // condiciones de borde
    for(int i = 0; i < N; i++){
        mat[0][i] = 0.0;
        mat[N-1][i] = 0.0;
        mat[i][0] = 0.0;
        mat[i][N-1] = 0.0;
    }
}

void relaxation_step(double mat[N][N] ){
    int i,j;
    for(i = 1; i < N-2 ; i++)
        for(j = 1; j < N-2 ; j++)
            mat[i][j] = 0.25*(mat[i+1][j] + mat[i-1][j] + mat[i][j+1] + mat[i][j-1]);
}

void compute_E( double U[N][N], double Ex[N][N], double Ey[N][N]){
    int i,j;
    for(i = 1; i < N-1; i++){
        for(j = 1; j < N-1; j++){
            Ey[i][j] = 1/(2*h)*( U[i+1][j] - U[i-1][j] );
            Ex[i][j] = 1/(2*h)*( U[i][j+1] - U[i][j-1] );
        }
    }
}

void write( FILE *fp, double mat[N][N] ){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            fprintf(fp,"%f \t", mat[i][j]);
        }
        fprintf(fp,"\n");
    }
}
