#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nvec 40000000

int asmfunc(short *mat, char *vec, long n, float *dest);

int main(void) {
    float dest[16] __attribute__ ((aligned (64)));
    short mat[16*16*2];
    char *vec;
    int i, j, n, p;
    clock_t start, end;
    double cpu_time_used;

    for (j=0; j<16; j++) {
        for (i=0; i<16; i++) {
            p = (i * 16 + j) * 2;
            if (i == j) {
                mat[p] = 1;
                mat[p+1] = 1;
            } else {
                mat[p] = 0;
                mat[p+1] = 0;
            }
        }
    }

    /* random values (or 0?) */
    vec = malloc(16*nvec);

    for (i=0; i<10; i++) {
        start = clock();
        asmfunc(mat, vec, nvec, dest);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Datasize: %d x 16 bytes  CPU time : %.5f\n", nvec, cpu_time_used);
    }

    free(vec);
    return 0;
}
