#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;

float T = 40.0;
float rho = 10.0;
float L = 100.0;
float c = sqrt(T/rho);
int n_puntos = 1000; 

void cond_inicial(float *u_i)
{
    for (int i=0; i<n_puntos;i++)
    {
        
        if (i <= 800)
        u_i[i] = (1.25*i/n_puntos);
   
        else
        u_i[i] = 5.0 - (5.0*i/n_puntos);
    
    }
}

void set_x(float *x)
{
    for (int i=0; i<n_puntos; i++)
    {
        x[i] = (L*i/n_puntos);
    }
}

void copia(float *u, float *u_c)
{
    for (int i=0; i<n_puntos; i++)
    {
        u_c[i] = u[i];
    }
}

void igualar(float *u,float *u2)
{
    for (int i=0; i<n_puntos; i++)
    {
        u[i] = u2[i];
    }
}

void primer_paso(float *x, float *u_inicial,float *u_pasado,float *u_presente, float *u_futuro, float *u_inicial_copia, float *u_futuro_copia)
{
    float dx = x[1] - x[0];
    float dt = 0.05001;
    float r = c*dt/dx;

    for (int i=1; i<n_puntos-1;i++)
    {
        u_futuro[i] = u_inicial[i] + (r*r/2.0)*(u_inicial[i+1] - 2.0*u_inicial[i] + u_inicial[i-1]);
    }

    copia(u_inicial,u_inicial_copia);
    igualar(u_pasado, u_inicial_copia);

    copia(u_futuro,u_futuro_copia);
    igualar(u_presente, u_futuro_copia);
 
}

void solucion(float *x, float *u_pasado,float *u_presente, float *u_futuro,float *u_presente_copia, float *u_futuro_copia, int t)
{

    float dx = x[1] - x[0];
    float dt = 0.05001; //0.02
    float r = c*dt/dx;

    for (int i= 0; i<t; i++)
    {
         for (int j= 1; j<n_puntos -1; j++)
         {
             u_futuro[j] = (2.0 - 2.0*r*r)*u_presente[j] - u_pasado[j] + (r*r)*(u_presente[j+1] + u_presente[j-1]);
         }

         copia(u_presente,u_presente_copia);
         igualar(u_pasado, u_presente_copia);

         copia(u_futuro,u_futuro_copia);
         igualar(u_presente, u_futuro_copia);

    }
}

void imprimirtxt(float **Matrizt)
{
    FILE *pf;
    //Abre archivo
    pf = fopen("cuerda.txt", "w"); 
    for (int i=0;i<n_puntos;i++)
    {
	for (int j=0;j<11;j++)
	{
		fprintf (pf, "%f %s",Matrizt[i][j]," ");
	}
	fprintf (pf,"\n");
    }
    fclose(pf);

}

void reiniciar(float *u_inicial, float *u_pasado, float *u_presente, float *u_futuro,float *u_inicial_copia, float *u_presente_copia, float *u_futuro_copia)
{
    for (int i=0; i<n_puntos; i++)
    {
        u_inicial[i] = 0;
        u_pasado[i] = 0;
        u_presente[i] = 0;
        u_futuro[i] = 0;
        u_inicial_copia[i] = 0;
        u_presente_copia[i] = 0;
        u_futuro_copia[i] = 0;
    } 
}

int main()
{
    float *u_inicial = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        u_inicial[i] = 0;

    float *u_pasado = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        u_pasado[i] = 0;

    float *u_presente = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        u_presente[i] = 0;

    float *u_futuro = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        u_futuro[i] = 0;

    float *u_inicial_copia = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        u_inicial_copia[i] = 0;

    float *u_presente_copia = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        u_presente_copia[i] = 0;

    float *u_futuro_copia = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        u_futuro_copia[i] = 0;

    float *x = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        x[i] = 0;

    float **Matriztiempos = (float **)malloc(n_puntos * sizeof(float *));
       for (int i=0; i<n_puntos; i++)
       Matriztiempos[i] = (float *)malloc(20 * sizeof(float));

    
    set_x(x);

   
 
    
    for (int i=0; i<n_puntos;i++)
    {
        for (int j=1; j<11;j++)
        {
            cond_inicial(u_inicial);
            primer_paso(x,u_inicial,u_pasado,u_presente,u_futuro,u_inicial_copia,u_futuro_copia);
            solucion(x, u_pasado,u_presente, u_futuro,u_presente_copia, u_futuro_copia, 20*(j-1));
            Matriztiempos[i][j] = u_presente[i];
            reiniciar(u_inicial,u_pasado,u_presente,u_futuro,u_inicial_copia,u_presente_copia,u_futuro_copia);
        }    
        
    }
    

    for (int i=0; i<n_puntos;i++)
    {
            Matriztiempos[i][0] = x[i];   
    }

    imprimirtxt(Matriztiempos);


    return 0;
}


