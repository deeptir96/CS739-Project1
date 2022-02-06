#include <stdio.h>
#include "udp.h"
#include <time.h>

#define BUFFER_SIZE (1000)

// client code
int main(int argc, char *argv[]) {
    struct sockaddr_in addrSnd, addrRcv;

    int sd = UDP_Open(20000);
    int rc = UDP_FillSockAddr(&addrSnd, "localhost", 10000);

    char message[BUFFER_SIZE];
    sprintf(message, "hello world");

    printf("client:: send message [%s]\n", message);
    //get time client send
    struct timespec t1, t2, t3;
    double diff1, diff2, diff3, diff4;

    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    rc = UDP_Write(sd, &addrSnd, message, BUFFER_SIZE);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    diff1 = (t2.tv_sec - t1.tv_sec);
    diff2 = (t2.tv_nsec - t1.tv_nsec);
    printf("Time diff = %f seconds, %f nanoseconds\n", diff1, diff2);

    //get time client send
    if (rc < 0) {
	printf("client:: failed to send\n");
	exit(1);
    }

    printf("client:: wait for reply...\n");
    //get time client rcv
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    rc = UDP_Read(sd, &addrRcv, message, BUFFER_SIZE);
    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
    diff1 = (t2.tv_sec - t1.tv_sec);
    diff2 = (t2.tv_nsec - t1.tv_nsec);
    printf("read Time diff = %f seconds, %f nanoseconds\n", diff1, diff2);
    printf("num bytes = %d\n", rc);
    //get time client rcv
    int numRetry = 0;
    while(rc < 0) {
	//timeout, tune later
//	sleep(50);
	numRetry++;
	printf("client:: retry %d\n", numRetry);
        rc = UDP_Write(sd, &addrSnd, message, BUFFER_SIZE);

    	if (rc < 0) {
            printf("client:: failed to send\n");
            exit(1);
        }
        rc = UDP_Read(sd, &addrRcv, message, BUFFER_SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &t3);
    diff3 = t3.tv_sec - t1.tv_sec;
    diff4 = t3.tv_nsec - t1.tv_nsec;
    printf("end read Time diff = %f seconds, %f nanoseconds\n", diff3, diff4);
    printf("client:: got reply [size:%d contents:(%s)\n", rc, message);
    return 0;
}

