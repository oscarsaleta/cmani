#include <stdlib.h>
#include <stdio.h>
#include "flux.h"

#define LMB -0.5
#define T0 0
#define T1 1
#define N 1
// 
#define TOL 1e-14
#define PASMIN 1e-6
#define PASMAX 0.5
#define NPASMX 10000
#define PAS0 0.01

// camp vectorial de y'=LMB*Y

int camp_lmb (int n, double t, double x[], double f[], void *prm) {
    f[0]=LMB*x[0];
    return 0;
}
// integrem desde t=T0 fins t=T1
int main (void) {
    double t=T0, x=1, h=PAS0;
    flux(&t,&x,&h,(T1-T0)/*T*/,PASMIN,PASMAX,TOL,NPASMX,N,camp_lmb,NULL);
    printf("solucio a temps %.16G es %.16G\n",t,x);
    return 0;
}