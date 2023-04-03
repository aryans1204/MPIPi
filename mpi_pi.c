#include <mpi.h>
#include <math.h>
#include <time.h>

int main(int argc,char*argv[])
{
        int done = 0, rank, process_count, i;
        long int n = 1000000000;
        double derivative, pi, sum, x, intermediate_pi;
        long int step_count = 100;
        int proc_count = 1;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &process_count);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        time_t time1 = clock();

        while (!done) {
                MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
                derivative = 1.0 / (double) n;
                sum = 0.0;

                for (i = rank+1; i <= n; i+=process_count) {
                        x = derivative * (double) i;
                        sum += sqrt(1-x*x);
                        if (i == step_count) {
                                double inst_time = (clock() - time1) / (double) CLOCKS_PER_SEC;
                                printf("The estimated time is %2lf at integration step %li and process count %d\n", inst_time, step_count, process_count);
                                step_count *= 10;
                        }
                }
                intermediate_pi = derivative * sum;

                MPI_Reduce(&intermediate_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
                if (rank == 0) {
                        printf("The estimated value of pi is %24f\n", 4*pi);
                }
        }
        MPI_Finalize();
        return 0;
}
