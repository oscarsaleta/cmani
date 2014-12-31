#include <stdio.h>
#include <math.h>
#include "cmani.h"
#include "flux.h"
#include "sislin.h"

#define XPDV(i,j) xpdv[j*2*m+i]
#define DG(i,j) dg[j*m+i]

int cmani_gdg (int m, double x0[], double xf[], double dt, double dv[],
        double g[], double dg[], double pivfl[],
        double pas0, double pasmin, double pasmax, double tolfl, int npasmx,
        int (*camp)(int n, double t, double x[], double f[], void *prm),
        void *prm
        ) {

    int n=2*m*(1+2*m);
    double xpdv[n];
    double h = pas0;
    double t = 0;
    int i,j;
    
    /* Defineixo una matriu ampliada per usar el flux */
    for (i=0; i<m; i++) {
        xpdv[i] = x0[i];
        xpdv[i+m] = x0[i+m]+dv[i];
    }
    for (i=0; i<2*m; i++) {
        for (j=1; j<2*m+1; j++) {
            if (i==j-1)
                XPDV(i,j) = 1;
            else
                XPDV(i,j) = 0;
        }
    }
    
    /* Calculo el flux a temps 0 perquè el sistema és autònom */
    if (flux(&t,xpdv,&h,dt,pasmin,pasmax,tolfl,npasmx,2*m*(1+2*m),camp,prm) == -1) {
        return -1;
    }

    /* Agafo les projeccions que interessen */
    for (i=0; i<m; i++) {
        g[i] = xpdv[i]-xf[i];
        pivfl[i] = xpdv[i+m];
    }
    for (i=0; i<m; i++) {
        for (j=0; j<m; j++) {
            DG(i,j) = xpdv[(j+m+1)*2*m+i];
        }
    }

    return 0;

}
#undef XPDV
#undef DG

int cmani (int m, double x0[], double xf[], double dt, double dv[],
        double tol, int maxit,
        double pas0, double pasmin, double pasmax, double tolfl, int npasmx,
        int (*camp)(int n, double t, double x[], double f[], void *prm),
        void *prm
        ) {

    double g[m],dg[m*m],pivfl[m],olddv[m];
    double dgaux[m*m];
    double corr[m], normsq, normcorr, normdifdv;
    int i,j,k;

    /* Resolem el sistema de (5), G(dv0)=0, pel mètode de Newton */
    for (k=0; k<maxit; k++) {

        /* Passo a cmani_gdg l'argument dv perquè només usaré les primeres m components */
        cmani_gdg(m,x0,xf,dt,dv,g,dg,pivfl,pas0,pasmin,pasmax,tolfl,npasmx,camp,prm);

        /* Calculo una còpia de dg perquè la resolució LU la sobreescriu */
        for (i=0; i<m; i++) {
            for (j=0; j<m; j++) {
                dgaux[j*m+i] = dg[j*m+i];
            }
        }

        printf("cmani():: it %d ",k);

        /* Criteri d'aturada: |G(dv)| < tol o bé |G(xk+1)-G(xk)| < tol */
        normsq = 0;
        normdifdv = 0;
        for (i=0; i<m; i++) {
            normdifdv += (dv[i]-olddv[i])*(dv[i]-olddv[i]);
            normsq += g[i]*g[i];
        }
        printf("ng %g ",sqrt(normdifdv));
        if ( sqrt(normsq) < tol || (k>0 && normdifdv < tol*tol) )
            break;

        /* Ens cal resoldre DG*corr=G */
        gauss(m,dgaux,g,corr);

        /* Ara apliquem la correcció a dv0 */
        normcorr = 0;
        for (i=0; i<m; i++) {
            olddv[i] = dv[i];
            dv[i] -= corr[i];
            normcorr += corr[i]*corr[i];
        }
        printf("nc %g\n",sqrt(normcorr));
        
        if (k==maxit-1) {
            fprintf(stderr,"cmani():: assolit nombre màxim d'iteracions de Newton %d\n",maxit);
        }
    }

    /* Ara aïllem dv1 de (4) */
    cmani_gdg(m,x0,xf,dt,dv,g,dg,pivfl,pas0,pasmin,pasmax,tolfl,npasmx,camp,prm);
    for (i=0; i<m; i++) {
        dv[i+m] = xf[i+m]-pivfl[i];
    }

    printf("\ndv[]\n");
    for (i=0; i<2*m; i++)
        printf("  %25.17g\n",dv[i]);

    return 0;
}


