#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>


int main()
{
	printf("My Process ID is %d\n", getpid());
	printf("My Parent's process ID is %d\n",getppid());

	exit(0);

}
