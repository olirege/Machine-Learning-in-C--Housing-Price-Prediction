#include "./utils.h"
// Function to calculate the mean of a feature
double calculate_mean(HouseData *data, int numPoints, FeatureAccessor accessor) {
    double sum = 0.0;
    for(int i = 0; i < numPoints; ++i) {
        sum += accessor(&data[i]);
    }
    return sum / numPoints;
}