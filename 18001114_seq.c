#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 100
#define NUMLIMIT 70.0
#define RANDLIMIT 5

// Matrix initialization
float a[N][N];
float b[N][N];
float c[N][N];

// Time constructor creation
struct timeval start, stop;


// Random matrix generatior
void init_matrixes(){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j] = (double)(rand()% RANDLIMIT);
            b[i][j] = (double)(rand()% RANDLIMIT);
        }        
    }
    
}

// Display input matrixes
void display_input_matrixes(){
    printf("Matrix A : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.3f\t", a[i][j]);
        }
        printf("\n\n");
    }

    printf("Matrix B : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.3f\t", b[i][j]);
        }
        printf("\n\n");
    }
    
}

// Display output matrixes
void display_answer(){
    printf("Matrix C : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.3f\t", c[i][j]);
        }
        printf("\n\n");
    }
}


// Main method
int main()
{
    printf("Sequantial Execution\n\n");

    gettimeofday(&start, 0); // start the timing

    init_matrixes();

    // Matrix multiplication 
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    gettimeofday(&stop, 0); // end the timing

    // print results and inputs
    #ifdef PRINT
        display_input_matrixes();
        display_answer();
    #endif

    // print the timing details
    double start_time = stop.tv_sec + stop.tv_usec*1e-6;
    double end_time = start.tv_sec + start.tv_usec*1e-6;
    double tim_diff = (stop.tv_sec + stop.tv_usec*1e-6) - (start.tv_sec + start.tv_usec*1e-6);
    printf("Start = %.6f\n", start_time);
    printf("End = %.6f\n", end_time);
    printf("Time = %.6f\n\n", tim_diff);

    return 0;
}