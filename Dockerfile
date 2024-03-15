FROM alpine:3.14

# Install system dependencies
RUN apk add --no-cache g++ make

# Prepare files
RUN mkdir /app
RUN mkdir /app/src
COPY ./src ./app/src
COPY ./Makefile ./app/Makefile
WORKDIR /app

# Build
RUN make app
RUN make test

# Cleanup
RUN rm -rf /src
RUN rm Makefile
