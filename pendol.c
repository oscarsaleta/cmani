#include <math.h>

#define N 2

int pendol (int n, double t, double x[], double f[], void *prm) {

    f[0]=x[1];
    f[1]=-sin(x[0]);
    if (n>N) {
        f[2] = x[3];
        f[3] = -x[2]*cos(x[0]);
        f[4] = x[5];
        f[5] = -x[4]*cos(x[0]);
    }

    return 0;
}

#undef N
