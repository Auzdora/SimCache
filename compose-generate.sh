#!/bin/bash

# Validate command line arguments
if [[ "$#" -ne 2 ]]; then
    echo "Usage: $0 <number_of_instances> <image_name>"
    exit 1
fi

# Get parameters
instances=$1
image_name=$2

# Validate instances number
if ! [[ "$instances" =~ ^[0-9]+$ ]]; then
    echo "Error: The number of instances must be a positive integer."
    exit 1
fi

# Create docker-compose.yaml file
echo "version: '3'" > docker-compose.yaml
echo "services:" >> docker-compose.yaml

# Generate service definitions
for ((i=0; i<instances; i++)); do
    echo "  cache_server_$i:" >> docker-compose.yaml
    echo "    image: $image_name" >> docker-compose.yaml
    echo "    ports:" >> docker-compose.yaml
    echo "      - \"$((9527+$i)):9527\"" >> docker-compose.yaml
    echo "    environment:" >> docker-compose.yaml
    echo "      - ME=$i" >> docker-compose.yaml
    echo "      - TOTAL=$instances" >> docker-compose.yaml
done

# Feedback
echo "Generated docker-compose.yaml with $instances instances using image $image_name."
