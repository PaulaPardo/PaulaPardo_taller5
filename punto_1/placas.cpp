#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;

int n = 512; //n = L/h
float V0 = 100.0;
int N = 524288; // N = 2*(L/h)^2
int i_1 = 154-1;
int i_2 = 358-1;
int j_1 = 205-1; 
int j_2 = 307-1;

void iniciar(float **M)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            M[i][j] = 0.0;
        }
    }

    for (int i=i_1; i<i_2; i++)
    {
        M[i][j_1] = -V0/2;
    }

    for (int i=i_1; i<i_2; i++)
    {
        M[i][j_2] = V0/2;
    }

    for (int i=i_1; i<i_2; i++)
    {
        for (int j=(j_1+1); j<(j_2); j++)
        {
            M[i][j] = V0;
        }
    }
}

void imprimir(float **M)
{
   FILE *pf = fopen("potencial.txt", "w+");
   for (int i=0; i<n; i++)
   {
        for (int j=0; j<n; j++)
        {
            fprintf(pf,"%f %s", M[j][i]," ");
        }
   fprintf(pf,"\n") ;
   } 
}

void imprimirx(float **grad)
{
   FILE *pf_2 = fopen("campoE_x.txt", "w+");
   for (int i=0; i<n; i++)
   {
        for (int j=0; j<n; j++)
        {
            fprintf(pf_2,"%f %s", grad[i][j]," ");
        }
   fprintf(pf_2,"\n") ;
   } 
}

void imprimiry(float **grad)
{
   FILE *pf_3 = fopen("campoE_y.txt", "w+");
   for (int i=0; i<n; i++)
   {
        for (int j=0; j<n; j++)
        {
            fprintf(pf_3,"%f %s", grad[i][j]," ");
        }
   fprintf(pf_3,"\n") ;
   } 
}



void laplace(float **M)
{
    for(int k=0; k<N; k++)
    {
        for(int i =1; i< n-1; i++)
        {
            for(int j=1; j<n-1; j++)
            {
                if(!(i>=i_1 && i<=i_2 && j>=j_1 && j<=j_2))
	        {
	    	    M[i][j] = 0.25*(M[i+1][j] + M[i][j+1] + M[i-1][j] + M[i][j-1]); 	
	        }
            }
        }
    }
}

void grady(float **M, float **grad)
{
    int k=0;
    float h=5.0/512.0;
    float *vec = (float *)malloc((n*n) * sizeof(float));
    float *vecp = (float *)malloc((n*n) * sizeof(float));
    for(int i=0; i<n;i++)
    {
        for(int j=0; j<n; j++)
        {
            vec[k++] = M[i][j]; 
        }
    }

    for(int i=0; i<(n*n); i++)
    {
        vecp[i] = (vec[i]-vec[i-1])/h; 
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            grad[i][j] = -1.0*vecp[i+j*n];
        }
    }
}

void gradx(float **M, float **grad)
{
    int k_2=0;
    float h_2=5.0/512.0;
    float *vec_2 = (float *)malloc((n*n) * sizeof(float));
    float *vec_2p = (float *)malloc((n*n) * sizeof(float));
    for(int i=0; i<n;i++)
    {
        for(int j=0; j<n; j++)
        {
            vec_2[k_2++] = M[j][i]; 
        }
    }

    for(int i=0; i<(n*n); i++)
    {
        vec_2p[i] = (vec_2[i]-vec_2[i-1])/h_2; 
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            grad[i][j] = -1.0*vec_2p[i+j*n];
        }
    }
}

int main()
{

    float **Matriz = (float **)malloc(n * sizeof(float *));
    for (int i=0; i<n; i++)
    {
        Matriz[i] = (float *)malloc(n* sizeof(float));
    }

    float **gradiente_x = (float **)malloc(n * sizeof(float *));
    for (int i=0; i<n; i++)
    {
        gradiente_x[i] = (float *)malloc(n* sizeof(float));
    }

    float **gradiente_y = (float **)malloc(n * sizeof(float *));
    for (int i=0; i<n; i++)
    {
        gradiente_y[i] = (float *)malloc(n* sizeof(float));
    }
    
    iniciar(Matriz);
    laplace(Matriz);
    gradx(Matriz, gradiente_x);
    grady(Matriz, gradiente_y);
    imprimir(Matriz);
    imprimirx(gradiente_x);
    imprimiry(gradiente_y);
    return 0;
}
