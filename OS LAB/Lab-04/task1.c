#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void evenSum(int n)
{
	int sum=0;
	for(int i=1;i<=n;i++){
		if(!(i%2)) sum+=i;
	}
	printf("Sum of even numbers in Child Process:%d\n",sum);
}

void oddSum(int n)
{
        int sum=0;
        for(int i=1;i<=n;i++){
                if(i&1) sum+=i;
        }
        printf("Sum of odd numbers in Parent Process:%d\n",sum);
}

int main()
{
	int n;
	printf("Enter n:");
	scanf("%d",&n);

	int pid;

	switch(pid=fork()){
		case 0:
			oddSum(n);
		        break;
		default:
			evenSum(n);
			break;
		case -1:
			perror("fork");
			exit(1);

	}

	return 0;
}

