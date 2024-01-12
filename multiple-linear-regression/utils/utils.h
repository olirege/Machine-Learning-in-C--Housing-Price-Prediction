#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// HouseData structure to store data from csv file
typedef struct {
    int price;
    int area;
    int bedrooms;
    int bathrooms;
    int stories;
    int mainroad; // 1 for yes, 0 for no
    int guestroom; // 1 for yes, 0 for no
    int basement; // 1 for yes, 0 for no
    int hotwaterheating; // 1 for yes, 0 for no
    int airconditioning; // 1 for yes, 0 for no
    int parking;
    int prefarea; // 1 for yes, 0 for no
    int furnishingstatus; // 1 for furnished, 2 for semi-furnished, 0 for unfurnished
} HouseData;

typedef double (*FeatureAccessor)(HouseData*); // Function pointer type for accessing features
double area_accessor(HouseData* data);
double bedrooms_accessor(HouseData* data);
double bathrooms_accessor(HouseData* data);
double stories_accessor(HouseData* data);
// Function to read data from csv file
int read_data(const char *filename, HouseData **data, int *numPoints);
// Function to shuffle data -- Fisher-Yates shuffle
int shuffle_data(HouseData *data, int numPoints);
// Function to split data into training and testing sets -- 70/30 split
int split_data(HouseData *data, int numPoints, HouseData **trainingSet, int *trainingSize, HouseData **validatingSet, int *validatingSize, HouseData **testingSet, int *testingSize);
// Function to train the model
int train_data(HouseData *trainingSet, int trainingSize, HouseData *validatingSet, int validatingSize, double *coefficients);
// Function to calculate the prediction
double calculate_prediction(HouseData data, double *coefficients);
// Function to test the model
int test_data(HouseData *testingSet, int testingSize, double *coefficients, double *predictions);
// Function to calculate the mean of a feature
double calculate_mean(HouseData *data, int numPoints, FeatureAccessor accessor);
// Function to calculate the standard deviation of a feature
double calculate_std(HouseData *data, int numPoints, FeatureAccessor accessor, double mean);
#endif