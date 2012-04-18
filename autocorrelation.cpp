#include <iostream>
#include "cstdio"

#include "simd.h"

#define NUM_TRIALS	10

#if !defined(NUM)
#define NUM 32 
#endif

#define GNUPLOT 1

#define PRINT_SIMD 1
#define PRINT_NOSIMD 1
#define PRINT_DIFFERENCE 1


float Ranf(float, float);
int Ranf(int, int);

// shift aray right one space and use the last element as the first
// FAIL! this will evenutally cause a segfault.
#define shift_arr(a, l, t) t=a[l-1];a-=1;a[0]=t;


// shift aray right one space and use the last element as the first
void shift_array_right(float *arr, int length) {
    float temp[length];
    for(int i = 0; i < length; ++i) {
        temp[i] = arr[i];
    }
    arr[0] = temp[length - 1];
    for(int i = 1; i < length; ++i) {
        arr[i] = temp[i - 1];
    }
}

// for testing
void print_array(float *arr, int length) {
    for(int i = 0; i < length; ++i) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[ ]) {

    float temp;
    float *A = (float*) malloc(NUM* sizeof (float));
    if (A == NULL) {
        perror("malloc failed");
    }
    float *B = (float*) malloc(NUM* sizeof (float));
    if (B == NULL) {
        perror("malloc failed");
    }
    float *C = (float*) malloc(NUM* sizeof (float));
    if (C == NULL) {
        perror("malloc failed");
    }
    double prec = omp_get_wtick();
    //fprintf( stderr, "Clock precision = %g\n", prec );

    for (int i = 0; i < NUM; i++) {
        A[i] = Ranf(-10.f, 10.f);
        B[i] = Ranf(-10.f, 10.f);
    }

    //print_array(A, NUM);
    //shift_array_right(A, NUM);
    //print_array(A, NUM);
    /****************************
     * SIMD test block
     * **************************/
    double time0 = Timer();
    for (int t = 0; t < NUM_TRIALS; t++) {
        for(int j = 0; j < NUM; j++) {
            C[j] = SimdMulAndSum(A, B, NUM);
            //shift_arr(B, NUM, temp);
            print_array(A, NUM); // testing
            print_array(B, NUM); 
            print_array(C, NUM);
            std::cout << std::endl;
        }
    }
    double time1 = Timer();
    double dts = (time1 - time0) / (float) NUM_TRIALS;
    if (PRINT_SIMD == 1) {
        if(GNUPLOT == 0) {
            printf("Average SIMD Elapsed time = %g\n", dts);
            printf("SIMD speed = %8.3f MFLOPS\n", ((float) (NUM * NUM) / dts) / 1000000.f);
        } else {
            // x-axis: #-of-elements y-axis: MFLOPS, do not need elapsed time
            printf("%d %8.3f\n", NUM, ((float) (NUM * NUM) / dts) / 1000000.f);
        }
    }

    /****************************
     * non SIMD test block
     * **************************/
    double time2 = Timer();
    for (int t = 0; t < NUM_TRIALS; t++) {
        for(int j = 0; j < NUM; j++) {
            C[j] = NonSimdMulAndSum(A, B, NUM);
            shift_arr(B, NUM, temp);
        }
    }
    double time3 = Timer();

    double dtn = (time3 - time2) / (float) NUM_TRIALS;
    if(PRINT_NOSIMD == 1) { 
        if(GNUPLOT == 0) {
            printf("Average Non-SIMD Elapsed time = %g\n", dtn);
            printf("Non-SIMD speed = %8.3f MFLOPS\n", ((float) (NUM * NUM) / dtn) / 1000000.f);
            //printf("Speed-up = %g\n", dtn / dts);
        } else {
            // x-axis: #-of-elements y-axis: MFLOPS, do not need elapsed time
            printf("%d %8.3f\n", NUM, ((float) (NUM * NUM) / dtn) / 1000000.f);
        }
    }
    if(PRINT_DIFFERENCE == 1) {
        printf("%d %g\n", NUM, ((float) NUM / dtn) / (dtn/dts));
    }
    return 0;
}

float Ranf(float low, float high) {
    float r = (float) rand(); // 0 - RAND_MAX
    return ( low + r * (high - low) / (float) RAND_MAX);
}

int Ranf(int ilow, int ihigh) {
    float low = (float) ilow;
    float high = (float) ihigh + 0.9999f;
    return (int) (Ranf(low, high));
}
