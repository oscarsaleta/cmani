#include <stdio.h>
#include <math.h>

#define A(i,j) a[(j)*n+(i)]

void lu_desc (int n, double *a, int piv, int s[]) {
   int i, j, k;
   for (i=0; i<n; i++) s[i]=i;
   for (k=0; k<=n-2; k++) {
   /* Faig pivotatge, si s'ha de fer */
      if (piv) {
	 double tmp=fabs(A(k,k));
	 int imax=k;
	 for (i=k+1; i<=n-1; i++)
	    if (fabs(A(i,k))>tmp) {
	       tmp=fabs(A(i,k));
	       imax=i;
	    }
	 if (imax!=k) {
	    /*fprintf(stderr, "%s(): pivoto %d amb %d\n",__func__,k,imax);*/
	    j=s[imax]; s[imax]=s[k]; s[k]=j;
	    for (j=0; j<=n-1; j++) {
	       tmp=A(imax,j); A(imax,j)=A(k,j); A(k,j)=tmp;
	    }
	 }
      }
   /* Faig eliminació gaussiana */
      for (i=k+1; i<=n-1; i++) {
	 A(i,k)/=A(k,k);
	 for (j=k+1; j<=n-1; j++) A(i,j)-=A(i,k)*A(k,j);
      }
   }
}

#undef A

#define A(i,j) a[(j)*n+(i)]
#define B(i,j) b[(j)*n+(i)]
#define X(i,j) x[(j)*n+(i)]

void lu_res (int n, double *a, int s[], int p, double *b, double *x) {
   int i, j, k;
   double y[n];
   for (k=0; k<=p-1; k++) {
   /* Substitució cap endavant */
      for (i=0; i<=n-1; i++) {
	 y[i]=B(s[i],k);
	 for (j=0; j<=i-1; j++)
	    y[i]-=A(i,j)*y[j];
      }
   /* Substitució cap endarrera */
      for (i=n-1; i>=0; i--) {
	 X(i,k)=y[i];
	 for (j=i+1; j<=n-1; j++)
	    X(i,k)-=A(i,j)*X(j,k);
	 X(i,k)/=A(i,i);
      }
   }
}

#undef X
#undef B
#undef A

/*
 * Resol un sistema d'equacions lineals pel mètode de Gauss
 * (descomposició LU amb pivotatge maximal per files). NO COMPROVA si
 * el sistema és singular!!
 *
 * Arguments:
 * - n (e) : número d'equacions i incògnites.
 * - a[] (e/s) : a l'entrada, matriu de coeficients, guardada per
 *   columnes. La sortida és inútil (es fa l'eliminació gaussiana sobre
 *   ella, però perquè fos útil caldria la informació dels
 *   intercanvis, que perdem).
 * - b[] (e) : terme independent.
 * - x[] (s) : solució del sistema.
 * 
 * No torna res.
 * 
 * ATENCIÓ! MATXACA la matriu de coeficients!!
 */

void gauss (int n, double a[], double b[], double x[]) {
   int s[n];
   lu_desc(n,a,1/*piv*/,s);
   lu_res(n,a,s,1/*p*/,b,x);
}
