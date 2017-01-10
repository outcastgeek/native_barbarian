FROM ubuntu:16.10
#FROM alpine:3.5

MAINTAINER outcastgeek <outcastgeek+docker@gmail.com>

RUN apt-get update

RUN apt-get install -y git build-essential python-pip cmake
#RUN apk add --update --no-cache git build-base make cmake python py2-pip bash

RUN pip install pip -U

RUN pip install conan

WORKDIR /workspace

CMD ["/bin/bash"]
