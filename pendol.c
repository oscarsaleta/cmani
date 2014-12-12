#include <math.h>
int pendol (int n, double t, double x[], double f[], void *prm) {
   f[0]=x[1];
   f[1]=-sin(x[0]);
   return 0;
}
