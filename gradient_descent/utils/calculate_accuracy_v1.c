#include "./utils.h"
#include "../matrix_operations/matrix_operations.h"

// Function to test the multi regression model
double calculate_accuracy(HouseData *testingSet, int testingSize, double *predictions, double *accuracy) {
    int numFeatures = 13; // Number of features excluding the price

    // Initialize the sum of squared errors
    double sumSquaredErrors = 0.0;

    // Calculate the sum of squared errors
    for (int i = 0; i < testingSize; ++i) {
        sumSquaredErrors += (testingSet[i].price - predictions[i]) * (testingSet[i].price - predictions[i]);
    }

    // Calculate the mean squared error
    double meanSquaredError = sumSquaredErrors / testingSize;
    if (meanSquaredError < 0) {
        perror("Error calculating mean squared error ");
        return 1;
    }

    // Calculate the root mean squared error
    double rootMeanSquaredError = sqrt(meanSquaredError);
    if (rootMeanSquaredError < 0) {
        perror("Error calculating root mean squared error ");
        return 1;
    }

    // Calculate the mean of the prices
    double meanPrice = 0.0;
    for (int i = 0; i < testingSize; ++i) {
        meanPrice += testingSet[i].price;
    }
    meanPrice /= testingSize;
    if (meanPrice < 0) {
        perror("Error calculating mean price ");
        return 1;
    }

    // Calculate the total sum of squares
    double totalSumSquares = 0.0;
    for (int i = 0; i < testingSize; ++i) {
        totalSumSquares += (testingSet[i].price - meanPrice) * (testingSet[i].price - meanPrice);
    }

    // Calculate the R-squared value
    double rSquared = 1.0 - (sumSquaredErrors / totalSumSquares);
    if (rSquared < 0) {
        perror("Error calculating R-squared value ");
        return 1;
    }
    // Calculate the adjusted R-squared value
    double adjustedRSquared = 1.0 - (1.0 - rSquared) * ((double)(testingSize - 1) / (double)(testingSize - numFeatures - 1));
    if (adjustedRSquared < 0) {
        perror("Error calculating adjusted R-squared value ");
        return 1;
    }
    // Store the accuracy
    *accuracy = adjustedRSquared;
    
    return 0; // Return success
}