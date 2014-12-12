#include "lorenz.h"

int lorenz(int n, double t, double x[], double f[], void *prm) {
    /* prm serà un punter a tres dobles (sigma, rho, beta) */
    double *params = prm;
    double sigma,rho,beta;
    sigma = params[0];
    rho = params[1];
    beta = params[2];

    f[0] = sigma*(x[1]-x[0]);
    f[1] = rho*x[0]-x[1]-x[0]*x[2];
    f[2] = x[0]*x[1]-beta*x[2];

    return 0;
}
