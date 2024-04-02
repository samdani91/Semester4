#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MIN_VALUE -1.0
#define MAX_VALUE 1.0


int total=0;
int circle=0;

void *calcPi(void *param);
float generate_random(float min, float max);
int inCircle(float x,float y);

int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&tid,&attr,calcPi,argv[1]);

    pthread_join(tid,NULL);

    float estPi=4*((float)circle/total);
    printf("%f\n",estPi);

}

void *calcPi(void *param)
{
    int n=atoi(param);

    srand(time(NULL));

    for(int i=0;i<n;i++){
        float x=generate_random(MIN_VALUE,MAX_VALUE);
        float y=generate_random(MIN_VALUE,MAX_VALUE);

        if(inCircle(x,y)){
            circle++;
        }
        total++;
    }

    pthread_exit(NULL);

}

float generate_random(float min, float max)
{
    float scale = rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

int inCircle(float x,float y)
{
    float dist=sqrt(pow(x,2)+pow(y,2));
    if(dist>1.00) return 0;
    else return 1;
}