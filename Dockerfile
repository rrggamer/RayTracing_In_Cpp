FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Tools + SDL2 headers/libs for building
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    libsdl2-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy only what we need (keeps image smaller, avoids copying your local build/)
COPY CMakeLists.txt ./
COPY *.cpp ./
# If you later add headers or src/ folder, add: COPY include/ include/  and/or  COPY src/ src/

# Configure + build
RUN cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
 && cmake --build build

# Run your compiled target
CMD ["./build/raytracing"]
