# Use Alpine Linux as the base image
FROM alpine:latest

# Install dependencies
RUN apk add --no-cache gcc musl-dev curl python3 py3-pip bash

# Install BLAS and LAPACK libraries (including cBLAS)
RUN apk add --no-cache openblas-dev lapack-dev
# Set up a Python virtual environment
RUN python3 -m venv /venv
ENV PATH="/venv/bin:$PATH"

# Install Kaggle CLI in the virtual environment
RUN pip install --no-cache-dir kaggle

# Create a directory for your application
WORKDIR /usr/src/app

# Copy the C source code, Kaggle API token, and the startup script into the container
COPY . .
COPY kaggle.json /root/.kaggle/kaggle.json

# Make sure the Kaggle API token is secure
RUN chmod 600 /root/.kaggle/kaggle.json

# Compile the C program
# Link against cBLAS and LAPACK
RUN gcc -o gradient_descent gradient_descent.c utils/read_data.c utils/shuffle_data.c utils/split_data.c utils/train_data.c utils/test_data.c utils/calculate_accuracy.c utils/calculate_mean.c utils/calculate_std.c utils/feature_accessors.c -lopenblas -llapack

# Command to run the startup script
CMD ["./initialize.sh"]
