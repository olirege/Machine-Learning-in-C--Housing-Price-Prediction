#include "./utils.h"

// Function to read data from csv file
int read_data(const char *filename, HouseData **data, int *numPoints) {
    // Open file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open the file");
        return 1;
    }
    // Allocate memory for data
    char line[1024]; // Buffer to read line
    int i = 0; // Line counter
    while (fgets(line, 1024, file)) {
        if (i == 0) { // Skip header line
            i++; // Increment line counter
            continue;
        }

        HouseData house; // Create a house object
        char *token = strtok(line, ","); // Split line by comma
        (*data)[i-1].price = atoi(token); // Convert string to integer

        token = strtok(NULL, ",");
        (*data)[i-1].area = atoi(token);

        token = strtok(NULL, ",");
        (*data)[i-1].bedrooms = atoi(token);

        token = strtok(NULL, ",");
        (*data)[i-1].bathrooms = atoi(token);

        token = strtok(NULL, ",");
        (*data)[i-1].stories = atoi(token);

        token = strtok(NULL, ",");
        (*data)[i-1].mainroad = (strcmp(token, "yes") == 0) ? 1 : 0;

        token = strtok(NULL, ",");
        (*data)[i-1].guestroom = (strcmp(token, "yes") == 0) ? 1 : 0;

        token = strtok(NULL, ",");
        (*data)[i-1].basement = (strcmp(token, "yes") == 0) ? 1 : 0;

        token = strtok(NULL, ",");
        (*data)[i-1].hotwaterheating = (strcmp(token, "yes") == 0) ? 1 : 0;

        token = strtok(NULL, ",");
        (*data)[i-1].airconditioning = (strcmp(token, "yes") == 0) ? 1 : 0;

        token = strtok(NULL, ",");
        (*data)[i-1].parking = atoi(token);

        token = strtok(NULL, ",");
        (*data)[i-1].prefarea = (strcmp(token, "yes") == 0) ? 1 : 0;

        token = strtok(NULL, ",");
        (*data)[i-1].furnishingstatus = (strcmp(token, "furnished") == 0) ? 1 : (strcmp(token, "semi-furnished") == 0) ? 2 : 0;

        i++; // Increment line counter
    }
    *numPoints = i - 1; // Set number of points
    fclose(file); // Close file
    return 0;
}