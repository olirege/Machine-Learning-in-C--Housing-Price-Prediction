#include "./utils.h"

// Function to test the linear regression model
int test_data(HouseData *testingSet, int testingSize, double *coefficients, double *predictions) {
    int numFeatures = 12; // Number of features excluding the price

    for (int i = 0; i < testingSize; ++i) {
        // Initialize prediction as the bias term (first coefficient)
        double prediction = coefficients[0]; // Assuming the first element in coefficients is the bias term

        // Add the contribution of each feature
        prediction += testingSet[i].area * coefficients[1];
        prediction += testingSet[i].bedrooms * coefficients[2];
        prediction += testingSet[i].bathrooms * coefficients[3];
        prediction += testingSet[i].stories * coefficients[4];
        prediction += testingSet[i].mainroad * coefficients[5];
        prediction += testingSet[i].guestroom * coefficients[6];
        prediction += testingSet[i].basement * coefficients[7];
        prediction += testingSet[i].hotwaterheating * coefficients[8];
        prediction += testingSet[i].airconditioning * coefficients[9];
        prediction += testingSet[i].parking * coefficients[10];
        prediction += testingSet[i].prefarea * coefficients[11];
        prediction += testingSet[i].furnishingstatus * coefficients[12];

        // Store the prediction
        predictions[i] = prediction;
    }

    return 0; // Return success
}