#include "./utils.h"
#include "../matrix_operations/matrix_operations.h"
// Function to train multiple linear regression model
int train_data(HouseData *trainingSet, int trainingSize, double *coefficients) {

    int m = trainingSize; // Number of training examples
    int n = 12 + 1; // Number of features + 1 (bias)

    // Allocate memory for X and y
    printf("Allocating memory for X and y\n");
    double *X = (double *)malloc(m * n * sizeof(double)); // Feature matrix
    double *y = (double *)malloc(m * sizeof(double)); // Target vector
    double *beta = (double *)malloc(n * sizeof(double)); // Parameter vector
    if (X == NULL || y == NULL || beta == NULL) {
        free(X); free(y); free(beta);
        perror("Error allocating memory for X and y");
        return 1; // Handle memory allocation failure
    }
    // Populate X and y
    printf("Populating X and y\n");
    populate_matrices(trainingSet, trainingSize, X, y);
    
    // Calculate X^T * X
    printf("Calculating X^T * X\n");
    double *XtX = (double *)malloc(n * n * sizeof(double));
    if (XtX == NULL) {
        free(X); free(y); free(beta); free(XtX);
        perror("Error allocating memory for XtX");
        return 1; // Handle memory allocation failure
    }
    matrix_multiply(X, X, XtX, n, n, m);
    printf("XtX:\n");
    print_matrix(XtX, n, n);

    // Add Ridge Regression term (lambda * I)
    printf("Adding Ridge Regression term (lambda * I)\n");
    double lambda = 0.01;  // Example regularization parameter
    for (int i = 0; i < n; i++) {
        XtX[i * n + i] += lambda;
    }
    printf("XtX + lambda * I:\n");
    print_matrix(XtX, n, n);
    // Calculate inverse of X^T * X
    printf("Calculating inverse of X^T * X\n");
    if (invert_matrix(XtX, n) != 0) {
        free(X); free(y); free(beta); free(XtX);
        return 1; // Handle matrix inversion failure
    }

    // Calculate X^T * y
    printf("Calculating X^T * y\n");
    double *Xty = (double *)malloc(n * sizeof(double));
    if (Xty == NULL) {
        free(X); free(y); free(beta); free(XtX); free(Xty);
        perror("Error allocating memory for Xty");
        return 1; // Handle memory allocation failure
    }
    matrix_multiply(X, y, Xty, n, 1, m);
    printf("Xty:\n");
    print_matrix(Xty, n, 1);

    // Calculate beta = (X^T * X)^{-1} * (X^T * y)
    printf("Calculating beta = (X^T * X)^{-1} * (X^T * y)\n");
    matrix_multiply(XtX, Xty, beta, n, 1, n);
    
    // Copy coefficients to the output parameter
    printf("Copying coefficients to the output parameter\n");
    for (int i = 0; i < n; ++i) {
        coefficients[i] = beta[i];
    }

    // Free allocated memory
    printf("Freeing allocated memory\n");
    free(X);
    free(y);
    free(beta);
    free(XtX);
    free(Xty);
    return 0;
}
