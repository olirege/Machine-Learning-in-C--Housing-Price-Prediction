#include "./utils.h"
int train_data(HouseData *trainingSet, int trainingSize, HouseData *validatingSet, int validatingSize, double *coefficients) {
    int m = trainingSize; // Number of training examples
    int n = 12 + 1; // Number of features + 1 (bias)
    // Hyperparameters
    double learningRate = 0.04; 
    int iterations = 1200;
    int epochs = 10;
    printf("Hyperparameters: learningRate = %lf, iterations = %d, epochs = %d\n", learningRate, iterations, epochs);
    double bestValidationError = INFINITY;
    int noImprovementInEpochs = 0;
    const int patience = 20; // Number of epochs to wait for improvement before stopping
    // Initialize coefficients
    for (int i = 0; i < n; i++) {
        coefficients[i] = 0.0;
    }
    // Gradient Descent
    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int iter = 0; iter < iterations; iter++) {
            double gradients[n];
            memset(gradients, 0, sizeof(gradients));
            // Calculate gradients
            for (int i = 0; i < m; i++) {
                // Calculate predicted value
                double predicted = calculate_prediction(trainingSet[i], coefficients);

                // Calculate error
                double error = predicted - trainingSet[i].price;
                gradients[0] += error; // Gradient for bias term
                gradients[1] += error * trainingSet[i].area;
                gradients[2] += error * trainingSet[i].bedrooms;
                gradients[3] += error * trainingSet[i].bathrooms;
                gradients[4] += error * trainingSet[i].stories;
                gradients[5] += error * trainingSet[i].mainroad;
                gradients[6] += error * trainingSet[i].guestroom;
                gradients[7] += error * trainingSet[i].basement;
                gradients[8] += error * trainingSet[i].hotwaterheating;
                gradients[9] += error * trainingSet[i].airconditioning;
                gradients[10] += error * trainingSet[i].parking;
                gradients[11] += error * trainingSet[i].prefarea;
                gradients[12] += error * trainingSet[i].furnishingstatus;
            }

            // Update coefficients
            for (int j = 0; j < n; j++) {
                coefficients[j] -= (learningRate / m) * gradients[j];
            }
        }
        printf("Epoch %d completed\n", epoch + 1);
        // Calculate cost
        double cost = 0.0;
        for (int i = 0; i < m; i++) {
            // Calculate predicted value
            double predicted = calculate_prediction(trainingSet[i], coefficients);
            // Calculate error
            double error = predicted - trainingSet[i].price;
            cost += error * error;
        }
        cost /= (2 * m);
        printf("Cost: %lf\n", cost);
        
        // Check for convergence
        if (cost < 0.0001) {
            printf("Converged\n");
            break;
        }

        // Calculate validation error
        double validationError = 0.0;
        for (int i = 0; i < validatingSize; i++) {
            double predicted = calculate_prediction(validatingSet[i], coefficients);
            double error = predicted - validatingSet[i].price;
            validationError += error * error;
        }
        validationError /= validatingSize;

        printf("Epoch %d, Training Cost: %lf, Validation Error: %lf\n", epoch + 1, cost, validationError);

        // Check for early stopping
        if (validationError < bestValidationError) {
            printf("Validation error improved from %lf to %lf\n", bestValidationError, validationError);
            bestValidationError = validationError;
            noImprovementInEpochs = 0;
        } else {
            printf("Validation error did not improve\n");
            noImprovementInEpochs++;
            if (noImprovementInEpochs >= patience) {
                printf("Early stopping: Validation error not improving\n");
                break;
            }
        }
    }

    return 0; // Success
}

double calculate_prediction(HouseData data, double *coefficients) {
    double predicted = coefficients[0]; // Bias term
    predicted += coefficients[1] * data.area;
    predicted += coefficients[2] * data.bedrooms;
    predicted += coefficients[3] * data.bathrooms;
    predicted += coefficients[4] * data.stories;
    predicted += coefficients[5] * data.mainroad;
    predicted += coefficients[6] * data.guestroom;
    predicted += coefficients[7] * data.basement;
    predicted += coefficients[8] * data.hotwaterheating;
    predicted += coefficients[9] * data.airconditioning;
    predicted += coefficients[10] * data.parking;
    predicted += coefficients[11] * data.prefarea;
    predicted += coefficients[12] * data.furnishingstatus;
    return predicted;
}