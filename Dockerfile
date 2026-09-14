FROM debian:unstable-slim

RUN apt-get update && apt-get install -y \
    cmake \
    g++-16 \
    gcc-16 \
    libstdc++-16-dev \
    gdb \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gcc-16
ENV CXX=g++-16

WORKDIR /app
