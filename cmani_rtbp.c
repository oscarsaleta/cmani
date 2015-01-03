#include <stdio.h>
#include "cmani.h"
#include "rtbps.h"

#define CAMP rtbps
#define N 6
#define M 3
#define PRM params

/* constants per rk78 */
#define PASMIN 1e-5
#define PASMAX 0.5
#define TOL 1e-12
#define NPASMX 1000000
#define PAS0 0.01


int main (int argc, char *argv[]) {

    double params[1];
    double nwtparams[2];
    double x[2*N];
    double dv[N]; /* output del programa */
    double x0[N],xf[N];
    double dt;

    int i;

    /* Lectura d'arguments per línia de comanda */
    if (argc != 4
            || sscanf(argv[1],"%lf",&params[0])!=1
            || sscanf(argv[2],"%lf",&nwtparams[0])!=1
            || sscanf(argv[3],"%lf",&nwtparams[1])!=1
       ) {
        fprintf(stderr,"%s mu tolwnt maxitnwt\n",argv[0]);
        return -1;
    }

    /* Bucle del programa */
    while ( scanf("%lf",&x[0])==1 ) {
        /* Lectura d'arguments dins del programa */
        if (scanf("%lf",&dt)!=1) {
                fprintf(stderr, "%s: dt xi0 xi1 xi2 vi1 vi2 vi3 xf0 xf1 xf2 vf0 vf1 vf2\n",argv[0]);
                return -1;
        }
        for (i=1; i<2*N; i++) {
            if (scanf("%lf",&x[i])!=1) {
                fprintf(stderr, "%s: dt xi0 xi1 xi2 vi1 vi2 vi3 xf0 xf1 xf2 vf0 vf1 vf2\n",argv[0]);
                return -1;
            }
        }

        /* Definim x0 i xf i inicialitzem dv = 0 */
        for (i=0; i<N; i++) {
            x0[i] = x[i];
            xf[i] = x[i+N];
            dv[i] = 0;
        }

        cmani(M,x0,xf,dt,dv,nwtparams[0],(int)nwtparams[1],PAS0,PASMIN,PASMAX,TOL,NPASMX,CAMP,params);

        for (i=0; i<N; i++)
            printf("%22.15E ",dv[i]);

    }
        



    return 0;
}
