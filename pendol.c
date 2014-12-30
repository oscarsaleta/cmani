#include <math.h>

#define N 2

int pendol (int n, double t, double x[], double f[], void *prm) {

    f[0]=x[1];
    f[1]=-sin(x[0]);
    if (n>N) {
        f[2] = 0;
        f[3] = -cos(x[0]);
        f[4] = 1;
        f[5] = 0;
    }

    return 0;
}

#undef N
