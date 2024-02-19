#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 100

void multiplyRow(int row, int col, int mat1[][MAX_SIZE], int mat2[][MAX_SIZE], int result[][MAX_SIZE]) {
    for (int j = 0; j < col; j++) {
        int sum = 0;
        for (int k = 0; k < col; k++) {
            sum += mat1[row][k] * mat2[k][j];
        }
        result[row][j] = sum;
    }
}

int main() {
    int row1, col1, row2, col2;

    printf("Enter the number of rows and columns for matrix 1: ");
    scanf("%d %d", &row1, &col1);

    printf("Enter the number of rows and columns for matrix 2: ");
    scanf("%d %d", &row2, &col2);

    if (col1 != row2) {
        printf("Matrices cannot be multiplied\n");
        return 1;
    }

    int mat1[MAX_SIZE][MAX_SIZE], mat2[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];

    printf("Enter elements of matrix 1:\n");
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter elements of matrix 2:\n");
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }

    pid_t pid;
    for (int i = 0; i < row1; i++) {
        pid = fork();
        if (pid == 0) { // Child process
            multiplyRow(i, col2, mat1, mat2, result);
            printf("Row %d multiplication completed by process %d\n", i, getpid());
            return 0;
        } else if (pid < 0) { // Error
            fprintf(stderr, "Fork failed\n");
            return 1;
        }
    }

    // Parent process waits for all child processes to complete
    for (int i = 0; i < row1; i++) {
        wait(NULL);
    }

    printf("Resultant matrix:\n");
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
