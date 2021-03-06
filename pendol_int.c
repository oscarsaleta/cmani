#include <stdio.h>
#include "flux.h"
#include "pendol.h"

#define CAMP pendol
#define N N_PENDOL
#define PRM params

/* rkf ordre 7 i 8 amb tol 1e-12 -> passos entre 1e-1 i 1e-2 */
#define PASMIN 1e-4
#define PASMAX 0.5
#define TOL 1e-12
#define NPASMAX 1000000
#define PAS0 0.01

int main (int argc, char *argv[]) {
    void *params=NULL;
    double x[N],T,t,h,dT;
    int np;
    /* Dummy variables are dummy */
    int i,j;

    /* lectura de dades */
    while ( scanf("%lf",&x[0])==1 ) {
        for (i=1; i<N; i++) {
            if (scanf("%lf",&x[i])!=1) {
                fprintf(stderr, "%s: x0 x1 ... xN T np\n",argv[0]);
                return -1;
            }
        }
        if (scanf("%lf %d", &T, &np)!=2) {
            fprintf(stderr, "%s: x0 x1 ... xN T np\n",argv[0]);
            return -1;
        }

        dT = T/np;
        t=0;
        h=PAS0;
        /* imprimim el primer punt perquè el primer iterat ja fa un pas dT */
        printf("%22.15E ",t);
        for (i=0; i<N; i++)
            printf("%22.15E ",x[i]);
        printf("%22.15E\n",h);
        /* calculem el flux */
        for (j=0; j<np; j++) {
            flux(&t,&x[0],&h,dT,PASMIN, PASMAX, TOL, NPASMAX, N, CAMP, PRM);
            printf("%22.15E ",t);
            for (i=0; i<N; i++)
                printf("%22.15E ",x[i]);
            printf("%22.15E\n",h);
        }
        printf("\n\n");

    }

    return 0;
}
