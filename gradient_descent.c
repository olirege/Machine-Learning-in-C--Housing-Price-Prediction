    #include "./utils/utils.h"

    int main()
    {
        setbuf(stdout, NULL);
        printf("Hello, World!\n");
        // Step 1 - allocate memory for data
        printf("Allocating memory for data\n");
        HouseData *data = (HouseData *)malloc(1000 * sizeof(HouseData)); // Pointer to HouseData structure
        if (!data)
        {
            perror("Error allocating memory for data\n");
            return 1;
        }

        printf("Reading data from csv file\n");
        // Step 2 - read data from csv file
        const char *filename = "Housing.csv";
        int numPoints = 0;      // Number of data points
        if (read_data(filename, &data, &numPoints) != 0)
        { // Populate data
            perror("Error reading data from csv file\n");
            free(data);
            return 1;
        }
        
        // Step 3 - shuffle data
        printf("Shuffling data\n");
        if (shuffle_data(data, numPoints) != 0)
        { // Shuffle data
            perror("Error shuffling data\n");
            free(data);
            return 1;
        }
        // Step 3.5 - Normalize data
        printf("Calculating mean and standard deviation for normalization\n");
        double mean_area = calculate_mean(data, numPoints, area_accessor);
        double mean_bedrooms = calculate_mean(data, numPoints, bedrooms_accessor);
        double mean_bathrooms = calculate_mean(data, numPoints, bathrooms_accessor);
        double mean_stories = calculate_mean(data, numPoints, stories_accessor);
        double stddev_area = calculate_std(data, numPoints, area_accessor, mean_area);
        double stddev_bedrooms = calculate_std(data, numPoints, bedrooms_accessor, mean_bedrooms);
        double stddev_bathrooms = calculate_std(data, numPoints, bathrooms_accessor, mean_bathrooms);
        double stddev_stories = calculate_std(data, numPoints, stories_accessor, mean_stories);
        // Normalize data
        printf("Normalizing data\n");
        for(int i = 0; i < numPoints; i++) {
            data[i].area = (data[i].area - mean_area) / stddev_area;
            data[i].bedrooms = (data[i].bedrooms - mean_bedrooms) / stddev_bedrooms;
            data[i].bathrooms = (data[i].bathrooms - mean_bathrooms) / stddev_bathrooms;
            data[i].stories = (data[i].stories - mean_stories) / stddev_stories;
        }

        // Step 4 - split data into training, validating and testing sets -- 60/20/20 split
        printf("Splitting data into training and testing sets\n");
        HouseData *trainingSet = NULL; 
        int trainingSize = 0;
        HouseData *validatingSet = NULL;
        int validatingSize = 0;
        HouseData *testingSet = NULL;
        int testingSize = 0;
        if (split_data(data, numPoints, &trainingSet, &trainingSize, &validatingSet, &validatingSize, &testingSet, &testingSize) != 0)
        { // Split data
            perror("Error splitting data into training and testing sets\n");
            free(data);
            free(trainingSet);
            free(validatingSet);
            free(testingSet);
            return 1;
        }

        // Step 5 - train model
        printf("Training model\n");
        double *coefficients = (double *)malloc((12 + 1) * sizeof(double)); // Allocate memory for coefficients
        if (!coefficients) {
            perror("Error allocating memory for coefficients\n");
            free(data);
            free(trainingSet);
            free(validatingSet);
            free(testingSet);
            return 1;
        }
        if(train_data(trainingSet, trainingSize, validatingSet, validatingSize, coefficients) != 0) {
            perror("Error training model ");
            free(data);
            free(trainingSet);
            free(validatingSet);
            free(testingSet);
            free(coefficients);
            return 1;
        }
        // Step 6 - test model
        printf("Testing model\n");
        double *predictions = (double *)malloc(testingSize * sizeof(double)); // Allocate memory for predictions
        if (!predictions) {
            perror("Error allocating memory for predictions ");
            free(data);
            free(trainingSet);
            free(validatingSet);
            free(testingSet);
            free(coefficients);
            return 1;
        }
        if(test_data(testingSet, testingSize, coefficients, predictions) != 0) {
            perror("Error testing model ");
            free(data);
            free(trainingSet);
            free(validatingSet);
            free(testingSet);
            free(coefficients);
            free(predictions);
            return 1;
        }
     
        //Step 7 - print results
        printf("Printing results\n");
        // printf("Accuracy: %lf\n", accuracy);
        printf("Predictions:\n");
        double avgErrorRate = 0.0;
        for(int i = 0; i < testingSize; i++) {
            printf("%lf - %lf = %lf\n", predictions[i], testingSet[i].price, predictions[i] - testingSet[i].price);
            avgErrorRate += (predictions[i] - testingSet[i].price) / testingSet[i].price;
        }
        printf("Average Error Rate: %lf\n", avgErrorRate);
        // Last Step - free memory
        printf("Freeing memory\n");
        free(coefficients);
        free(trainingSet);
        free(validatingSet);
        free(testingSet);
        free(data);
        return 0;
    }