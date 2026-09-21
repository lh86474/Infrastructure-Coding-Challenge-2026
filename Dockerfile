FROM ubuntu:22.04

# to remove geographic prompt while building
ARG DEBIAN_FRONTEND=noninteractive

# Locales
RUN <<EOF
apt update && apt install -y locales
locale-gen en_US en_US.UTF-8
EOF

ENV LC_ALL=en_US.UTF-8
ENV LANG=en_US.UTF-8

# Setup Sources
RUN <<EOF
apt install -y software-properties-common
add-apt-repository universe
apt update && apt install curl -y
EOF

ARG ROS_APT_SOURCE_VERSION
ENV ROS_APT_SOURCE_VERSION=${ROS_APT_SOURCE_VERSION}

RUN curl -L -o /tmp/ros2-apt-source.deb "https://github.com/ros-infrastructure/ros-apt-source/releases/download/${ROS_APT_SOURCE_VERSION}/ros2-apt-source_${ROS_APT_SOURCE_VERSION}.$(. /etc/os-release && echo ${UBUNTU_CODENAME:-${VERSION_CODENAME}})_all.deb"
RUN dpkg -i /tmp/ros2-apt-source.deb

# Install ROS 2 packages
RUN <<EOF
apt update
apt upgrade -y
apt install -y ros-humble-ros-base
EOF

#Install colcon
RUN apt install -y python3-colcon-common-extensions

#Install git
RUN apt install -y git-all

#Install rosdep and get rosdep started
RUN <<EOF
apt install -y python3-rosdep
rosdep init
rosdep update
EOF

# Activate ros2 in bash shell
RUN echo "source /opt/ros/humble/setup.bash" >> /root/.bashrc

# Install g++
RUN <<EOF
apt-get update 
apt-get install -y build-essential
EOF

#Install vim
RUN apt install -y vim
