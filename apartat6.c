#include <stdio.h>
#include <math.h>
#include "cmani.h"
#include "pendol.h"

#define TOLNWT 1e-12
#define MAXIT 25

#define PAS0 0.01
#define PASMIN 1e-4
#define PASMAX 0.5
#define TOLFL 1e-12
#define NPASMX 1000000
#define CAMP pendol

int main (int argc, char *argv[]) {
    
    int m=1;
    double x0[] = {1,0};
    double dv[] = {0,0};
    double xf[] = {0,-0.95885108};
//    double xf[] = {0,-sqrt(2.*(1.-cos(1.)))};
//    double dt = M_PI/2.;
    double dt = 1.57079633;

    cmani(m,&x0[0],&xf[0],dt,&dv[0],TOLNWT,MAXIT,PAS0,PASMIN,PASMAX,TOLFL,NPASMX,CAMP,NULL);

    return 0;
}
