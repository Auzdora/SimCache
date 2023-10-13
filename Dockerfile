# Use ubuntu 20.04 as OS
FROM ubuntu:20.04

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update and install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    curl \
    git \
    libssl-dev \
    libsystemd-dev \
    libmsgpack-dev \
    libasio-dev \
    libboost-all-dev


# NOTE: this is only used in final test environment
COPY ./build/bin/simcache-server /myapp/simcache-server

# # ENTRYPOINT
ENTRYPOINT ["/myapp/simcache-server"]