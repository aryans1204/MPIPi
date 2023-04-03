#include <stdio.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv)
{
    long int i;
    double x, fx, sum, pi;
    double inst_time;
    
    time_t time1 = clock();
    long int step_count = 100;
    
    sum = 0.0;
    double derivative = 1.0 / (double) 1000000000;

    for (i = 0; i <= 1000000000; i++) {
        x = derivative * (double) i;
        fx = sqrt(1-x*x);
        sum = sum + fx;
        
        if (step_count == i) {
            inst_time = (clock() - time1) / (double) CLOCKS_PER_SEC;
            printf("Elapsed time (s) = %.2lf at step count %li\n", inst_time, step_count);
            step_count *= 10;
        }
    }
         
    pi = derivative*sum;

    double final_time = (clock() - time1) / (double) CLOCKS_PER_SEC;

    printf("The value of pi obtained is %.24f\n", 4*pi);
    printf("Elapsed time (s) = %.2lf\n", final_time);

    return 0;
}

