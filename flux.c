#include <stdio.h>
#include <math.h>
#include "rk78.h"
#include "flux.h"

#define SIG(t) ((t)>0?1:-1)
/**
 * Calcula el flux d'un sistema d'EDOs des de temps t fins t+T
 * usant rk78().
 */
int flux (double *t, double x[], double *h, double T, double pasmin, double pasmax, double tol, int npasmax, int n, int (*camp)(int n, double t, double x[], double f[], void *prm), void *prm) {
    int i=0;
    double tmax=*t+T; /* pot ser menor que *t */
    double haux;
    int sigT = SIG(T);
    /* si ens donen un temps negatiu i un pas positiu */
    if (SIG(*h)!=sigT)
        *h *= -1;

    while (i < npasmax) {
        /* si podem fer un pas sense passar-nos, el fem */
        if (fabs(*t+*h) < fabs(tmax)) {
            rk78(t,x,h,pasmin,pasmax,tol,n,camp,prm);
        }
        else {
            /* si no, fem una sèrie de passos fins arribar al final */
            haux=tmax-*t;
            while (fabs(*t+haux) <= fabs(tmax)) {
                if (fabs(haux) > pasmin) {
                    rk78(t,x,&haux,pasmin,pasmax,tol,n,camp,prm);
                }
                else
                    rk78(t,x,&haux,haux,pasmax,tol,n,camp,prm);
            }
            return 0;
        }
        i++;
        
    }
    fprintf(stderr,"flux():: nombre màxim d'iteracions %d assolit\n",npasmax);
    return -1;
}

