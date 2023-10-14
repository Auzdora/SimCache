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

# Copy the source code into the image
COPY . /myapp

# Build the project
WORKDIR /myapp
RUN rm -rf build && mkdir build && cd build && cmake ..

# Build the third-party json library
WORKDIR /myapp/third_party/json
RUN rm -rf build && mkdir build && cd build && cmake .. && make -j4 && make install

# Build the project
WORKDIR /myapp/build
RUN make -j 4

# # NOTE: this is only used in final test environment
# COPY ./build/bin/simcache-server /myapp/simcache-server

# # ENTRYPOINT
ENTRYPOINT ["/myapp/build/bin/simcache-server"]