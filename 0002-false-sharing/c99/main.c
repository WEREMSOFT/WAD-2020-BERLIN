#include <sys/times.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>

struct timespec tmsBegin1, tmsEnd1, tmsBegin2, tmsEnd2, tmsBegin3, tmsEnd3;

int array[100];

void *heavy_loop(void *param) {
    int index = *((int *) param);
    int i;
    for (i = 0; i < 100000000; i++)
        array[index] += 3;
}

void fix_time(struct timespec* start, struct timespec* finish, long long *seconds, long long *ns){
    if (start->tv_nsec > finish->tv_nsec) { // clock underflow
        --(*seconds);
        (*ns) += 1000000000;
    }
}

void print_results(long long *seconds, long long *ns){
    printf("seconds without ns: %ld\n", *seconds);
    printf("nanoseconds: %ld\n", *ns);
    printf("total seconds: %ld\n", *seconds + *ns/1000000000);
}

int main(int argc, char *argv[]) {
    int first_elem = 0;
    int bad_elem = 1;
    int good_elem = 32;
    long int time1s, time1ns;
    long int time2s, time2ns;
    long int time3s, time3ns;
    pthread_t thread_1;
    pthread_t thread_2;

    clock_gettime(CLOCK_REALTIME, &tmsBegin3);
    heavy_loop((void *) &first_elem);
    heavy_loop((void *) &bad_elem);
    clock_gettime(CLOCK_REALTIME, &tmsEnd3);

    clock_gettime(CLOCK_REALTIME, &tmsBegin1);
    pthread_create(&thread_1, NULL, heavy_loop, (void *) &first_elem);
    pthread_create(&thread_2, NULL, heavy_loop, (void *) &bad_elem);
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    clock_gettime(CLOCK_REALTIME, &tmsEnd1);

    clock_gettime(CLOCK_REALTIME, &tmsBegin2);
    pthread_create(&thread_1, NULL, heavy_loop, (void *) &first_elem);
    pthread_create(&thread_2, NULL, heavy_loop, (void *) &good_elem);
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    clock_gettime(CLOCK_REALTIME, &tmsEnd2);

    printf("%d %d %d\n", array[first_elem], array[bad_elem], array[good_elem]);
    time1ns = (tmsEnd1.tv_nsec - tmsBegin1.tv_nsec);
    time2ns = (tmsEnd2.tv_nsec - tmsBegin2.tv_nsec);
    time3ns = (tmsEnd3.tv_nsec - tmsBegin3.tv_nsec);

    time1s = (tmsEnd1.tv_sec - tmsBegin1.tv_sec);
    time2s = (tmsEnd2.tv_sec - tmsBegin2.tv_sec);
    time3s = (tmsEnd3.tv_sec - tmsBegin3.tv_sec);

    fix_time(&tmsBegin1, &tmsEnd1, &time1s, &time1ns);
    fix_time(&tmsBegin2, &tmsEnd2, &time2s, &time2ns);
    fix_time(&tmsBegin3, &tmsEnd3, &time3s, &time3ns);

    printf("With false sharing :\n");
    print_results(&time1s, &time1ns);

    printf("\nWithout false sharing :\n");
    print_results(&time2s, &time2ns);
    printf("\nSequential no thread :\n");
    print_results(&time3s, &time3ns);

    printf("No thread / False Sharing ratio: %.2f%\n", (float)((float)time1ns / (float)time3ns) * 100.0);
    printf("No false sharing / False Sharing ratio: %.2f%\n", (float)((float)time1ns / (float)time2ns) * 100.0);
    printf("No thread / No False Sharing ratio: %.2f%\n", (float)((float)time3ns / (float)time2ns) * 100.0);

    return 0;
}