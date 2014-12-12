#include <stdio.h>
#include "rk78.h"
#include "flux.h"

/**
 * Calcula el flux d'un sistema d'EDOs des de temps t fins t+T
 * usant rk78().
 */
int flux (double *t, double x[], double *h, double T, double pasmin, double pasmax, double tol, int npasmax, int n, int (*camp)(int n, double t, double x[], double f[], void *prm), void *prm) {
    int i=0;
    double tmax=*t+T,haux;
    
    while (i < npasmax) {
        /* si podem fer un pas sense passar-nos, el fem */
        if (*t+*h < tmax)
            rk78(t,x,h,pasmin,pasmax,tol,n,camp,prm);
        else {
            /* si no, fem un pas forçant arribar al final */
            haux=tmax-*t;
            while (*t+haux <= tmax) {
                if (haux > pasmin)
                    rk78(t,x,&haux,pasmin,pasmax,tol,n,camp,prm);
                else
                    rk78(t,x,&haux,haux,pasmax,tol,n,camp,prm);
            }
            return 0;
        }
        i++;
        
    }
    return -1;
}

