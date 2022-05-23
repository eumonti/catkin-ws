FROM ubuntu:18.04

LABEL org.opencontainers.image.source="https://github.com/AlessandroBiaggi/catkin-ws"

ADD https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc /tmp/ros.asc
RUN apt-get update && apt-get install -y --no-install-recommends gnupg2 && \
    apt-key add /tmp/ros.asc

RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu bionic main" > /etc/apt/sources.list.d/ros-latest.list'
RUN apt-get update && apt-get install -y --no-install-recommends ros-melodic-desktop-full
