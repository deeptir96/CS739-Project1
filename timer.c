#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(int argc, char** argv) {
	struct timespec t1, t2;
        double diff1, diff2;
	long val = 0;

	int loop_iters = 1;
	if(argc == 2) {
		loop_iters = atoi(argv[1]);
	}

	clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
	for(int i = 0; i < loop_iters; i++) {
		val++;
	}
	clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
	diff1 = (t2.tv_sec - t1.tv_sec);
	diff2 = (t2.tv_nsec - t1.tv_nsec) / 1000000L;
        printf("Time diff = %f seconds, %f milliseconds\n", diff1, diff2);
	return 0;
}
