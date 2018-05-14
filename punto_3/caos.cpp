#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;

float dt = 0.006;
int t = 3000;
float a = 1.0/(2*pow(2,0.5));
float epsilon = 1.0; //con un epsilon tan pequeño de 10E-3 no se nota el caracter periodico de q1
int n_puntos = 500000; //n_puntos = (t/dt)

float f_prima_q1(float p1)
{ 
    float res = p1;
    return res;
}

float f_prima_q2(float p2)
{ 
    float res = p2;
    return res;
}

float f_prima_p1(float q1)
{ 
    float res = (-2.0*q1)/(pow(4*pow(q1,2) + pow(epsilon,2), 1.5));
    return res;
}

float f_prima_p2(float q1,float q2)
{ 
    float res = (q1 - q2)/(sqrt((q1-q2)*(q1-q2) + epsilon*epsilon/4)*sqrt((q1-q2)*(q1-q2) + epsilon*epsilon/4)*sqrt((q1-q2)*(q1-q2) + epsilon*epsilon/4)) - (q1 + q2)/(sqrt((q1+q2)*(q1+q2) + epsilon*epsilon/4)*sqrt((q1-q2)*(q1-q2) + epsilon*epsilon/4)*sqrt((q1-q2)*(q1-q2) + epsilon*epsilon/4));
    return res;
}

void runge_kutta(float *q1,float *p1, float *t)
{
    q1[0] = a;
    p1[0] = 0.0;
    //q2[0] = 3;
    //p2[0] = 4;
    t[0] = 0.0;
    for (int i=1; i<n_puntos; i++)
    {
        float k1_q1 = dt * f_prima_q1(p1[i-1]);
        float k1_p1 = dt * f_prima_p1(q1[i-1]);
        float k2_q1 = dt * f_prima_q1(p1[i-1] + 0.5 * k1_p1);
        float k2_p1 = dt * f_prima_p1(q1[i-1] + 0.5 * k1_q1);
        float k3_q1 = dt * f_prima_q1(p1[i-1] + 0.5 * k2_p1);
        float k3_p1 = dt * f_prima_p1(q1[i-1] + 0.5 * k2_q1);
        float k4_q1 = dt * f_prima_q1(p1[i-1] + k3_p1);
        float k4_p1 = dt * f_prima_p1(q1[i-1] + k3_q1);


        float promedio_q1 = (1.0/6.0)*(k1_q1 + 2.0*k2_q1 + 2.0*k3_q1 + k4_q1);
       
        float promedio_p1 = (1.0/6.0)*(k1_p1 + 2.0*k2_p1 + 2.0*k3_p1 + k4_p1);
        
        q1[i] = q1[i-1] + promedio_q1;
     
        p1[i] = p1[i-1] + promedio_p1;
        
        t[i] = t[i-1] + dt;

    }
}

void runge_kutta2(float *q1,float *q2,float *p2)
{
    q2[0] = -a;
    p2[0] = 0.0;
    for (int i=1; i<n_puntos; i++)
    {
        float k1_q2 = dt * f_prima_q2(p2[i-1]);
        float k1_p2 = dt * f_prima_p2(q1[i-1],q2[i-1]);
        float k2_q2 = dt * f_prima_q2(p2[i-1] + 0.5 * k1_p2);
        float k2_p2 = dt * f_prima_p2(q1[i-1],q2[i-1] + 0.5 * k1_q2);
        float k3_q2 = dt * f_prima_q2(p2[i-1] + 0.5 * k2_p2);
        float k3_p2 = dt * f_prima_p2(q1[i-1],q2[i-1] + 0.5 * k2_q2);
        float k4_q2 = dt * f_prima_q2(p2[i-1] + k3_p2);
        float k4_p2 = dt * f_prima_p2(q1[i-1],q2[i-1] + k3_q2);

        float promedio_q2 = (1.0/6.0)*(k1_q2 + 2.0*k2_q2 + 2.0*k3_q2 + k4_q2);
       
        float promedio_p2 = (1.0/6.0)*(k1_p2 + 2.0*k2_p2 + 2.0*k3_p2 + k4_p2);
        
        q2[i] = q2[i-1] + promedio_q2;
       
        p2[i] = p2[i-1] + promedio_p2;
     

    }
}


void imprimir(float *q1, float *p1, float *q2, float *p2, float *t)
{
    FILE *pf;
    //Abre archivo
    pf = fopen("Runge-Kutta.txt", "w"); 
    for(int i=0; i<n_puntos; i++) 
    {
        fprintf(pf, "%f %f %f %f %f \n", t[i], q1[i], p1[i], q2[i], p2[i]);
    }
    fclose(pf);
}

void imprimirpantalla(float *q1, float *q2, float *p2)
{
    for(int i=0; i<n_puntos; i++)
    {
        if((q1[i]+q1[i+1])<q1[i] || (q1[i]+q1[i+1])<q1[i+1])
        {
            printf("%f %f \n", q2[i],p2[i]);
        }
    }
}

int main()
{
    float *q1 = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        q1[i] = 0;

    float *q2 = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        q2[i] = 0;

    float *p1 = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        p1[i] = 0;

    float *p2 = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        p2[i] = 0;

    float *t = (float*)malloc(n_puntos*sizeof(float)); 
    for (int i=0; i<n_puntos; i++)
        t[i] = 0;

    runge_kutta(q1,p1,t);
    runge_kutta2(q1,q2,p2);
    imprimirpantalla(q1,q2,p2);
    imprimir(q1,p1,q2,p2,t);

    return 0;
}

