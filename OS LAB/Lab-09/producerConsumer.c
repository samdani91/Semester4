#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>


pthread_t *producers;
pthread_t *consumers;

sem_t buffer_mutex, empty, full;

int *buffer, buffer_pos = -1, producer_count, consumer_count, buffer_len;


int produce(pthread_t self){
	int i = 0;
	int p = 1 + rand()%40;
	while(!pthread_equal(*(producers+i),self) && i < producer_count){
		i++;
	}
	printf("Producer %d produced %d \n",i+1,p);
	return p;
}


void consume(int p,pthread_t self){
	int i = 0;
	while(!pthread_equal(*(consumers+i),self) && i < consumer_count){
		i++;
	}

	printf("Buffer:");
	for(i=0;i<=buffer_pos;++i)
		printf("%d ",*(buffer+i));
	printf("\nConsumer %d consumed %d \nCurrent buffer len: %d\n",i+1,p,buffer_pos);
	
}


void* producer(void *args){
	while(true){
		int p = produce(pthread_self());
		sem_wait(&empty);
		sem_wait(&buffer_mutex);
		++buffer_pos;
		*(buffer + buffer_pos) = p; 
		sem_post(&buffer_mutex);
		sem_post(&full);
		sleep(1 + rand()%3);
	}
	return NULL;
}


void* consumer(void *args){
	int c;
	while(true){
		sem_wait(&full);
		sem_wait(&buffer_mutex);
		c = *(buffer+buffer_pos);
		consume(c,pthread_self());
		--buffer_pos;
		sem_post(&buffer_mutex);
		sem_post(&empty);
		sleep(1+rand()%5);
	}
	return NULL;
}

int main(void){
	
	int i,err;

	srand(time(NULL));

	sem_init(&buffer_mutex, 0, 1);
	sem_init(&full, 0, 0);

	printf("Enter the number of Producers: ");
	scanf("%d", &producer_count);
	producers = (pthread_t*) malloc(producer_count*sizeof(pthread_t));


	printf("Enter the number of Consumers: ");
	scanf("%d", &consumer_count);
	consumers = (pthread_t*) malloc(consumer_count*sizeof(pthread_t));


	printf("Enter buffer capacity: ");
	scanf("%d", &buffer_len);
	buffer = (int*) malloc(buffer_len*sizeof(int));


	sem_init(&empty,0,buffer_len);


	for(i=0; i<producer_count; i++){
		err = pthread_create(producers+i,NULL,&producer,NULL);
		if(err != 0){
			printf("Error creating producer %d: %s\n", i+1, strerror(err));
		}else{
			printf("Successfully created producer %d\n", i+1);
		}
	}

	for(i=0; i<consumer_count; i++){
		err = pthread_create(consumers+i,NULL,&consumer,NULL);
		if(err != 0){
			printf("Error creating consumer %d: %s\n", i+1, strerror(err));
		}else{
			printf("Successfully created consumer %d\n", i+1);
		}
	}

	for(i=0; i<producer_count; i++){
		pthread_join(*(producers+i), NULL);
	}
	for(i=0;i<consumer_count;i++){
		pthread_join(*(consumers+i), NULL);
	}
	return 0;
}