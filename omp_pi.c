#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NUM_THREADS 3

static long int num_steps = 1000000000;
double step;

int main()
{
        int i, j, k;
        double x;
        double pi;
        double sum=0.0;
        double start, delta;
        long int step_count = 100;
        int thread = 1;

        step = 1 / (double) num_steps;

        for (j = 1; j <= NUM_THREADS; j++) {
                omp_set_num_threads(j);
                sum = 0.0;
                double start = omp_get_wtime();

                #pragma omp parallel for reduction(+:sum) private(x)
                for (i = 0; i <= num_steps; i++) {
                        x = i*step;
                        sum += sqrt(1-x*x);
                        if (i == step_count) {
                                delta = omp_get_wtime()-start;
                                printf("Elapsed time is %2lf at integration step %li and thread count %d\n", delta, step_count, thread);
                                step_count *= 10;
                        }
                        if (j == thread) {
                                delta = omp_get_wtime()-start;
                                printf("Elapsed time is %2lf at thread count %d\n", delta, thread);
                                thread++;
                        }
                }
        }
        pi = step*sum;

        printf("Estimated value of pi is %.24f\n", 4*pi);
        return 0;
}


