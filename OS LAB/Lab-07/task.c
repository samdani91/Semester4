#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int min=1e5;
int max=0;
int avg=0;

void *runner1(void *param);

int main(int argc,char *argv[])
{
    int n = argc - 1;
    int arr[n + 1]; 

    arr[0] = n;

    for (int i = 1; i <= n; i++) {
        arr[i] = atoi(argv[i]);
    }

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, runner1, arr);

    int *ptr;

    pthread_join(tid, (void **)&ptr);

    printf("Average:%i\n",*ptr);

}

void *runner1(void *param)
{
    int *arr=(int *)param;
    int n=arr[0];
    for(int i=1;i<=n;i++){
        //printf("%d ",arr[i]);
        avg+=arr[i];
    }
    avg/=n;

    pthread_exit(&avg);

}