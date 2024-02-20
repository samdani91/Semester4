#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void rowMultiply(int r1, int c1, int r2, int c2, int mat1[r1][c1], int mat2[r2][c2], int res[r1][c2], int i)
{
	for (int j = 0; j < c2; j++)
	{
		res[i][j] = 0;
		for (int k = 0; k < c1; k++)
		{
			res[i][j] += mat1[i][k] * mat2[k][j];
		}
	}
}

int main()
{
	int r1, c1, r2, c2;
	printf("Enter row and column for Matrix 1:");
	scanf("%d %d", &r1, &c1);
	printf("Enter row and column for Matrix 2:");
	scanf("%d %d", &r2, &c2);

	int mat1[r1][c1], mat2[r2][c2];

	if (c1 != r2)
	{
		printf("Matrix Multiplication Not Possible\n");
		return 0;
	}

	int res[r1][c2];

	printf("Enter matrix One\n");
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			scanf("%d", &mat1[i][j]);
		}
	}

	printf("Enter matrix Two\n");
	for (int i = 0; i < r2; i++)
	{
		for (int j = 0; j < c2; j++)
		{
			scanf("%d", &mat2[i][j]);
		}
	}

	printf("Result Matrix:\n");
	for (int i = 0; i < r1; i++)
	{
		int pid = fork();

		if (pid == -1)
		{
			perror("Fork");
			exit(1);
		}
		else if (pid == 0)
		{
			rowMultiply(r1, c1, r2, c2, mat1, mat2, res, i);
			for (int j = 0; j < c2; j++)
			{
				printf("%d ", res[i][j]);
			}
			printf("\n");
			exit(1);
		}
		wait(NULL);
	}

	
}
