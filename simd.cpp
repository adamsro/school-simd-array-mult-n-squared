#include "simd.h"

double Timer() {
    return omp_get_wtime();
}

void SimdSet(float *a, float b, int len) {
    float b4[4] = {b, b, b, b};

    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
    __asm
            (
            ".att_syntax\n\t"
            "movq    -40(%rbp), %rbx\n\t" // a
            "leaq    -32(%rbp), %rcx\n\t" // &b4[0]
            "movups	 (%rcx), %xmm1\n\t" // 4 copies of b in xmm1
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	%xmm1, (%rbx)\n\t" // store the result in a
                "addq $16, %rbx\n\t"
                );
    }

    for (int i = limit; i < len; i++) {
        a[i] = b;
    }
}

void SimdAdd(float *a, float *b, float *c, int len) {
    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
    __asm
            (
            ".att_syntax\n\t"
            "movq    -24(%rbp), %rbx\n\t" // a
            "movq    -32(%rbp), %rcx\n\t" // b
            "movq    -40(%rbp), %rdx\n\t" // c
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	(%rbx), %xmm0\n\t" // load the first sse register
                "movups	(%rcx), %xmm1\n\t" // load the second sse register
                "addps	%xmm1, %xmm0\n\t" // do the add
                "movups	%xmm0, (%rdx)\n\t" // store the result
                "addq $16, %rbx\n\t"
                "addq $16, %rcx\n\t"
                "addq $16, %rdx\n\t"
                );
    }

    for (int i = limit; i < len; i++) {
        c[i] = a[i] + b[i];
    }
}

void SimdAdd(float *a, float b, float *c, int len) {
    float b4[4] = {b, b, b, b};

    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
    __asm
            (
            ".att_syntax\n\t"
            "movq    -40(%rbp), %rbx\n\t" // a
            "leaq    -32(%rbp), %rcx\n\t" // &b4[0]
            "movups	 (%rcx), %xmm1\n\t" // 4 copies of b in xmm1
            "movq    -56(%rbp), %rdx\n\t" // c
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	(%rbx), %xmm0\n\t" // load the first sse register
                "addps	%xmm1, %xmm0\n\t" // do the add
                "movups	%xmm0, (%rdx)\n\t" // store the result
                "addq $16, %rbx\n\t"
                "addq $16, %rdx\n\t"
                );
    }

    for (int i = limit; i < len; i++) {
        c[i] = a[i] + b;
    }
}

void SimdSub(float *a, float *b, float *c, int len) {
    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
    __asm
            (
            ".att_syntax\n\t"
            "movq    -24(%rbp), %rbx\n\t" // a
            "movq    -32(%rbp), %rcx\n\t" // b
            "movq    -40(%rbp), %rdx\n\t" // c
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	(%rbx), %xmm0\n\t" // load the first sse register
                "movups	(%rcx), %xmm1\n\t" // load the second sse register
                "subps	%xmm1, %xmm0\n\t" // do the subtract
                "movups	%xmm0, (%rdx)\n\t" // store the result
                "addq $16, %rbx\n\t"
                "addq $16, %rcx\n\t"
                "addq $16, %rdx\n\t"
                );
    }

    for (int i = limit; i < len; i++) {
        c[i] = a[i] - b[i];
    }
}

void SimdSub(float *a, float b, float *c, int len) {
    float b4[4] = {b, b, b, b};

    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
    __asm
            (
            ".att_syntax\n\t"
            "movq    -40(%rbp), %rbx\n\t" // a
            "leaq    -32(%rbp), %rcx\n\t" // &b4[0]
            "movups	 (%rcx), %xmm1\n\t" // 4 copies of b in xmm1
            "movq    -56(%rbp), %rdx\n\t" // c
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	(%rbx), %xmm0\n\t" // load the first sse register
                "subps	%xmm1, %xmm0\n\t" // do the subtract
                "movups	%xmm0, (%rdx)\n\t" // store the result
                "addq $16, %rbx\n\t"
                "addq $16, %rdx\n\t"
                );
    }

    for (int i = limit; i < len; i++) {
        c[i] = a[i] - b;
    }
}

void SimdMul(float *a, float *b, float *c, int len) {
    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
    __asm
            (
            ".att_syntax\n\t"
            "movq    -24(%rbp), %rbx\n\t" // a
            "movq    -32(%rbp), %rcx\n\t" // b
            "movq    -40(%rbp), %rdx\n\t" // c
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	(%rbx), %xmm0\n\t" // load the first sse register
                "movups	(%rcx), %xmm1\n\t" // load the second sse register
                "mulps	%xmm1, %xmm0\n\t" // do the multiply
                "movups	%xmm0, (%rdx)\n\t" // store the result
                "addq $16, %rbx\n\t"
                "addq $16, %rcx\n\t"
                "addq $16, %rdx\n\t"
                );
    }

    for (int i = limit; i < len; i++) {
        c[i] = a[i] * b[i];
    }
}

void SimdMul(float *a, float b, float *c, int len) {
    float b4[4] = {b, b, b, b};

    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
    __asm
            (
            ".att_syntax\n\t"
            "movq    -40(%rbp), %rbx\n\t" // a
            "leaq    -32(%rbp), %rcx\n\t" // &b4[0]
            "movups	 (%rcx), %xmm1\n\t" // 4 copies of b in xmm1
            "movq    -56(%rbp), %rdx\n\t" // c
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	(%rbx), %xmm0\n\t" // load the first sse register
                "mulps	%xmm1, %xmm0\n\t" // do the multiply
                "movups	%xmm0, (%rdx)\n\t" // store the result
                "addq $16, %rbx\n\t"
                "addq $16, %rdx\n\t"
                );
    }

    for (int i = limit; i < len; i++) {
        c[i] = a[i] * b;
    }
}

void SimdDiv(float *a, float *b, float *c, int len) {
    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
    __asm
            (
            ".att_syntax\n\t"
            "movq    -24(%rbp), %rbx\n\t" // a
            "movq    -32(%rbp), %rcx\n\t" // b
            "movq    -40(%rbp), %rdx\n\t" // c
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	(%rbx), %xmm0\n\t" // load the first sse register
                "movups	(%rcx), %xmm1\n\t" // load the second sse register
                "divps	%xmm1, %xmm0\n\t" // do the divide
                "movups	%xmm0, (%rdx)\n\t" // store the result
                "addq $16, %rbx\n\t"
                "addq $16, %rcx\n\t"
                "addq $16, %rdx\n\t"
                );
    }

    for (int i = limit; i < len; i++) {
        c[i] = a[i] / b[i];
    }
}

void SimdDiv(float *a, float b, float *c, int len) {
    float b4[4] = {b, b, b, b};

    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
    __asm
            (
            ".att_syntax\n\t"
            "movq    -40(%rbp), %rbx\n\t" // a
            "leaq    -32(%rbp), %rcx\n\t" // &b4[0]
            "movups	 (%rcx), %xmm1\n\t" // 4 copies of b in xmm1
            "movq    -56(%rbp), %rdx\n\t" // c
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	(%rbx), %xmm0\n\t" // load the first sse register
                "divps	%xmm1, %xmm0\n\t" // do the divide
                "movups	%xmm0, (%rdx)\n\t" // store the result
                "addq $16, %rbx\n\t"
                "addq $16, %rdx\n\t"
                );
    }

    for (int i = limit; i < len; i++) {
        c[i] = a[i] / b;
    }
}

void NonSimdAdd(float *a, float *b, float *c, int len) {
    for (int i = 0; i < len; i++) {
        //c[i] = a[i] + b[i];
        *c++ = *a++ + *b++;
    }
}

void NonSimdAdd(float *a, float b, float *c, int len) {
    for (int i = 0; i < len; i++) {
        //c[i] = a[i] + b;
        *c++ = *a++ + b;
    }
}

void NonSimdSub(float *a, float *b, float *c, int len) {
    for (int i = 0; i < len; i++) {
        //c[i] = a[i] - b[i];
        *c++ = *a++ - *b++;
    }
}

void NonSimdSub(float *a, float b, float *c, int len) {
    for (int i = 0; i < len; i++) {
        //c[i] = a[i] - b;
        *c++ = *a++ - b;
    }
}

void NonSimdMul(float *a, float *b, float *c, int len) {
    for (int i = 0; i < len; i++) {
        //c[i] = a[i] * b[i];
        *c++ = *a++ * *b++;
    }
}

void NonSimdMul(float *a, float b, float *c, int len) {
    for (int i = 0; i < len; i++) {
        //c[i] = a[i] * b;
        *c++ = *a++ * b;
    }
}

void NonSimdDiv(float *a, float *b, float *c, int len) {
    for (int i = 0; i < len; i++) {
        //c[i] = a[i] / b[i];
        *c++ = *a++ / *b++;
    }
}

void NonSimdDiv(float *a, float b, float *c, int len) {
    for (int i = 0; i < len; i++) {
        //c[i] = a[i] / b;
        *c++ = *a++ / b;
    }
}

float SimdMulAndSum(float *a, float *b, int len) {
    float sum[4] = {0., 0., 0., 0.};
    int limit = (len / SSE_WIDTH) * SSE_WIDTH;
        /* instruction DESTINATION SOURCE */
    __asm
            (
            ".att_syntax\n\t"
            "movq    -56(%rbp), %rbx\n\t" // a
            "movq    -64(%rbp), %rcx\n\t" // b
            "leaq    -48(%rbp), %rdx\n\t" // &sum[0]
            "movups	 (%rdx), %xmm2\n\t" // 4 copies of 0. in xmm2
            );

    for (int i = 0; i < limit; i += SSE_WIDTH) {
        __asm
                (
                ".att_syntax\n\t"
                "movups	(%rbx), %xmm0\n\t" // load the first sse register
                "movups	(%rcx), %xmm1\n\t" // load the second sse register
                "mulps	%xmm1, %xmm0\n\t" // do the multiply
                "addps	%xmm0, %xmm2\n\t" // do the add
                "addq $16, %rbx\n\t"
                "addq $16, %rcx\n\t"
                );
    }

    __asm
            (
            ".att_syntax\n\t"
            "movups	 %xmm2, (%rdx)\n\t" // copy the sums back to sum[ ]
            );

    for (int i = limit; i < len; i++) {
        sum[i - limit] += a[i] * b[i];
    }

    return sum[0] + sum[1] + sum[2] + sum[3];
}

float NonSimdMulAndSum(float *a, float *b, int len) {
    float sum[4] = {0., 0., 0., 0.};
    int limit = (len / SSE_WIDTH) * SSE_WIDTH;

    for (int i = 0; i < limit; i++) {
        sum[0] += a[i] * b[i];
    }

    for (int i = limit; i < len; i++) {
        sum[i - limit] += a[i] * b[i];
    }

    return sum[0] + sum[1] + sum[2] + sum[3];
}
