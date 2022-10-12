#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>
#include <assert.h>

#define N 100
#define RANDLIMIT 5
#define THREADS 2 // define 2 threads

// Matrix initialization
float a[N][N];
float b[N][N];
float c[N][N];

// Time constructor creation
struct timeval start, stop;

// prototypes
void *slave(void *pid);

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

void *slave(void *pid)
{
    int x, low, high;

    // calculate which rows to calculate by each thread
    if (N >= THREADS)
    {
        x = N / THREADS;
        low = (int)pid * x; // low = 0 & high = 50
        high = low + x;     // low = 50 & high = 100
    }
    else
    {
        x = 1;
        low = (int)pid;
        if (low >= N)
        {
            high = low;
        }
        else
        {
            high = low + 1;
        }
    }

    int i, j, k;

    // Matrix multiplication (here mutal exclusion is not needed since each thread is accessing a different part of the array)
    for (int i = low; i < high; i++) // i for rows
    {
        for (int j = 0; j < N; j++) // j for columns
        {
            c[i][j] = 0;
            for (int k = 0; k < N; k++) // k for traversing
            {
                c[i][j] += a[i][k] * b[k][j];
            }
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

int main()
{   

    pthread_t tid[THREADS];

    gettimeofday(&start, 0); // start timing

    // create threads
    for (int i = 0; i < THREADS; i++)
    {
        if (pthread_create(&tid[i], NULL, slave, (void*)i) != 0)
        {
            perror("Pthread creation is failed...");
        }
        
    }
    
    // join threads
    for (int i = 0; i < THREADS; i++)
    {
        if (pthread_join(tid[i], NULL) != 0)
        {
            perror("Pthread join is failed...");
        }
        
    }
    

    gettimeofday(&stop, 0); // end timing

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