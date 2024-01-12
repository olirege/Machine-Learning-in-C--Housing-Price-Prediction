#include "./utils.h"

// Function to split data into training and testing sets
int shuffle_data(HouseData *data, int numPoints) {
    for (int i = 0; i < numPoints - 1; i++) { // Fisher-Yates shuffle
        int j = i + rand() / (RAND_MAX / (numPoints - i) + 1); // Random int such that i <= j < numPoints
        HouseData temp = data[j];
        data[j] = data[i];
        data[i] = temp;
    }
    return 0;
}