FROM alpine:3.14

RUN apk add --no-cache g++ make

RUN mkdir /app
RUN mkdir /app/src
COPY ./src ./app/src
COPY ./Makefile ./app/Makefile
WORKDIR /app

RUN make app
RUN make test
RUN rm -rf /src
RUN rm Makefile
