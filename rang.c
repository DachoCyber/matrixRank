#include <stdio.h>
#include <stdlib.h>

double min(double a, double b) {
    return (a < b) ? a : b;
}

int getRank(double** mat, int row, int col) {
    int rank = col;

    for (int i = 0; i < rank; ++i) {
        // Check if the pivot element is zero
        if (mat[i][i] != 0) {
            // Make all elements of this row 0 in the current column
            for (int j = 0; j < row; ++j) {
                if (j != i) {
                    // Calculate the factor by which the current row needs to be multiplied
                    double factor = mat[j][i] / mat[i][i];

                    // Subtract the current row multiplied by the factor from the other rows
                    for (int k = 0; k < rank; ++k) {
                        mat[j][k] -= factor * mat[i][k];
                    }
                }
            }
        } else {
            // If the pivot element is zero, find a non-zero pivot in the same column below
            int nonZeroRow = i + 1;
            while (nonZeroRow < row && mat[nonZeroRow][i] == 0) {
                ++nonZeroRow;
            }

            if (nonZeroRow < row) {
                // Swap rows to get a non-zero pivot
                for (int k = 0; k < rank; ++k) {
                    double temp = mat[i][k];
                    mat[i][k] = mat[nonZeroRow][k];
                    mat[nonZeroRow][k] = temp;
                }

                // Continue Gaussian elimination
                --i;
            } else {
                // If no non-zero pivot is found, set the rank to the current row
                rank = i;
                break;
            }
        }
    }

    return rank;
}

int main() { 
    
    int ROW, COL;
    printf("Enter the number of rows and coloumns:\n");
    scanf("%d%d", &ROW, &COL);
	
    double** mat = (double**)malloc(ROW * sizeof(double*));
    for (int i = 0; i < ROW; ++i) {
        mat[i] = (double*)malloc(COL * sizeof(double));
    }

    // Enter the matrix
    printf("Enter the matrix:\n");
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            scanf("%lf", &mat[i][j]); 
        }
        printf("\n");
    }

    int rank = getRank(mat, ROW, COL);

    printf("Rank of the matrix is: %d\n", rank);

    // Free allocated memory
    for (int i = 0; i < ROW; ++i) {
        free(mat[i]);
    }
    free(mat);

    return 0;
}

