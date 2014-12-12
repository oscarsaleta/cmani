#include <stdio.h>
#include "flux.h"
#include "rtbps.h"

#define CAMP rtbps
#define N 6
#define PRM params

/* rkf ordre 7 i 8 amb tol 1e-12 -> passos entre 1e-1 i 1e-2 */
#define PASMIN 1e-5
#define PASMAX 0.5
#define TOL 1e-12
#define NPASMAX 1000000
#define PAS0 0.01

#define DPHI(i,j) dphi[6*j+i]

int main (int argc, char *argv[]) {
    double params[1];
    double x[N],a[42],T,t,h,dT;
    double xm[N], xp[N], dx=1e-3, dphi[36];
    int np;
    /* Dummy variables are dummy */
    int i,j,k;

    /* lectura d'arguments al programa (no general)*/
    if (argc != 2
            || sscanf(argv[1],"%lf",&params[0])!=1
       ) {
        fprintf(stderr,"%s mu\n",argv[0]);
        return -1;
    }

    /* lectura de dades general? */
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
        h=PAS0;

        for (i=0; i<N; i++)
            a[i]=x[i];
        for (i=0; i<N; i++) {
            for (j=1; j<N; j++) {
                if (i==j-1)
                    a[j*N+i]= 1;
                else
                    a[j*N+i]=0;
            }
        }
            
        /* calculem el flux i A(t) */
        for (j=0; j<np; j++) {
            t=0;
            /* les 36 darreres components de a[N] són A(t) */
            flux(&t,&a[0],&h,dT,PASMIN,PASMAX,TOL,NPASMAX,42,CAMP,PRM);
            /* fem la diferencial del flux */
            /* necessitem dos vectors, un amb una component desplaçada
             * a la dreta i l'altre amb una component desplaçada
             * a l'esquerra
             */
            for (i=0; i<N; i++) {
                /* creo xp=(x+dx,y,z,vx,vy,vz) i xm=(x-dx,y,z,vx,vy,vz)
                 * i la resta, per generar una columna de Df amb cada parell
                 */
                for (k=0; k<N; k++) {
                    if (i==k) {
                        xp[k]=x[k]+dx;
                        xm[k]=x[k]-dx;
                    }
                    else
                        xp[k]=xm[k]=x[k];
                }
                /* reiniciar t i h */
                t=0; h=PAS0;
                /* calcular f(x-h) */
                flux(&t,&xm[0],&h,dT,PASMIN,PASMAX,TOL,NPASMAX,6,CAMP,PRM);
                /* reiniciar t i h */
                t=0; h=PAS0;
                /* calcular f(x+h) */
                flux(&t,&xp[0],&h,dT,PASMIN,PASMAX,TOL,NPASMAX,6,CAMP,PRM);
                    
                /* calcular una columna de Df */
                for (k=0; k<N; k++) {
                    DPHI(k,i)=(xp[k]-xm[k])/(2*dx);
                }
            }

            /* ja tenim Df, podem imprimir-la juntament amb A(t) i la seva diferència */
            for (i=0; i<36; i++)
                printf("%22.15E  %22.15E  %22.15E\n",a[i+5],dphi[i],a[i+5]-dphi[i]);
            printf("\n");
            /* guardem el pas fet a la primera crida al flux a x */
            for (i=0; i<N; i++)
                x[i]=a[i];
        }
        printf("\n\n");

    }

    return 0;
}
