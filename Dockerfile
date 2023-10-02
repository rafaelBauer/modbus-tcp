FROM debian:bullseye
LABEL Description="Build environment"

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
    build-essential \
    git \
    gdb \
    postgresql-server-dev-all \
    wget \
    clang-format \
    clang-tidy\
    clang \
    lld \
    ca-certificates \
    gnupg

# Install latest cmake
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | apt-key add -
RUN echo "deb https://apt.kitware.com/ubuntu/ bionic main" |  tee -a /etc/apt/sources.list
RUN apt-get update
RUN apt install -y cmake

## Work under /app directory
#RUN mkdir -p /app
#COPY . ./app
#WORKDIR /app
#
## Run cmake configure & build process
#RUN mkdir ./build
#RUN cmake -B ./build -S . -D CMAKE_BUILD_TYPE=Develop
#RUN cmake --build ./build
#
## Launch built application
#CMD ["./build/src/smart_bot"]
CMD ["/bin/bash"]
