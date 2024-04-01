#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int min=1e5;
int max=0;
double avg=0;

int n;
int *arr;

void *calcAvg(void *param);
void *calcMin(void *param);
void *calcMax(void *param);

int main(int argc,char *argv[])
{
    n = argc - 1;
    arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i+1]);
    }

    pthread_t tid[3];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&tid[0], &attr, calcAvg, NULL);
    pthread_create(&tid[1], &attr, calcMin, NULL);
    pthread_create(&tid[2], &attr, calcMax, NULL);

    for(int i=0;i<3;i++){
        pthread_join(tid[i],NULL);
    }

    printf("Average:%.2f\n",avg);
    printf("Minimum:%d\n",min);
    printf("Maximum:%d\n",max);

}

void *calcAvg(void *param)
{
    for(int i=0;i<n;i++){
        avg+=arr[i];
    }
    avg/=n;
    pthread_exit(NULL);
}

void *calcMin(void *param)
{
    for(int i=0;i<n;i++){
        if(arr[i]<min) min=arr[i];
    }
    pthread_exit(NULL);
}

void *calcMax(void *param)
{
    for(int i=0;i<n;i++){
        if(arr[i]>max) max=arr[i];
    }
    pthread_exit(NULL);
}