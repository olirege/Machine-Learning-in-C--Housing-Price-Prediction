#include "./utils.h"

// Function to split data into training and testing sets
int split_data(
    HouseData *data,
    int numPoints,
    HouseData **trainingSet,
    int *trainingSize,
    HouseData **validatingSet,
    int *validatingSize,
    HouseData **testingSet,
    int *testingSize) {
    // Assuming a 60/20/20 split for training/validating/testing
    *trainingSize = (int)(0.6 * numPoints);
    *validatingSize = (int)(0.2 * numPoints);
    *testingSize = numPoints - *trainingSize - *validatingSize;
    // Allocate memory for training, validating and testing sets
    *trainingSet = (HouseData *)malloc(*trainingSize * sizeof(HouseData));
    *validatingSet = (HouseData *)malloc(*validatingSize * sizeof(HouseData));
    *testingSet = (HouseData *)malloc(*testingSize * sizeof(HouseData));
    if (!(*trainingSet) || !(*validatingSet) || !(*testingSet)) {
        perror("Error allocating memory for training, validating and testing sets ");
        return 1;
    }
    // Copy data into training, validating and testing sets
    memcpy(*trainingSet, data, *trainingSize * sizeof(HouseData));
    memcpy(*validatingSet, data + *trainingSize, *validatingSize * sizeof(HouseData));
    memcpy(*testingSet, data + *trainingSize + *validatingSize, *testingSize * sizeof(HouseData));
    return 0;
}