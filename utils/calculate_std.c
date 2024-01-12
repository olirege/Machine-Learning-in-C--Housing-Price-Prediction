#include "./utils.h"
// Function to calculate the standard deviation of a feature
double calculate_std(HouseData *data, int numPoints, FeatureAccessor accessor, double mean) {
    double sum = 0.0;
    for(int i = 0; i < numPoints; ++i) {
        double value = accessor(&data[i]);
        sum += (value - mean) * (value - mean);
    }
    return sqrt(sum / numPoints);
}
