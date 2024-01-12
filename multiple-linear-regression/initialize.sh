#!/bin/bash

# Download the dataset from Kaggle
kaggle datasets download -d yasserh/housing-prices-dataset

# Unzip the dataset if it's zipped
unzip housing-prices-dataset.zip

# Check if the download was successful
if [ -f Housing.csv ]; then
    echo "Dataset downloaded successfully."
    # Run your application
    ./gradient_descent
else
    echo "Failed to download dataset."
    exit 1
fi
