#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    int n;
    printf("Enter n:");
    scanf("%d",&n);

    int even=0;
    int odd=0;
    int pid;

    switch(pid=fork()){
        case 0:
			for(int i=1;i<=n;i++){
                if(i&1){
                    odd+=i;
                }
            }
            printf("Sum of Odd numbers(Child Process):%d\n",odd);
			break;
		default:
			for(int i=1;i<=n;i++){
                if(!(i%2)){
                    even+=i;
                }
            }
            printf("Sum of Even numbers(Parent Process):%d\n",even);
			break;
		case -1:
			perror("fork");
			exit(1);
    }
    

    return 0;
}