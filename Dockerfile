FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y curl lsb-release gnupg2 software-properties-common build-essential && \
    add-apt-repository universe && \
    apt clean

# ROS 2 Foxy 
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null && \
    apt update && apt upgrade -y && \
    apt install -y ros-foxy-ros-base python3-colcon-common-extensions python3-vcstool python3-rosdep git ros-foxy-ament-cmake && \ 
    apt clean

ENV ROS_DISTRO=foxy
ENV ROS2_PATH=/opt/ros/foxy/

# Build SMACC 2
ENV COLCON_DEP_WS=/root/workspace/dep/ros_deps
SHELL ["/bin/bash", "-c"]

RUN mkdir -p ${COLCON_DEP_WS}/src && cd ${COLCON_DEP_WS}/src && \
    git clone https://github.com/robosoft-ai/SMACC2.git && \
    cd SMACC2 && \
    git checkout foxy && \
    source ${ROS2_PATH}/setup.bash && \
    cd ${COLCON_DEP_WS} && \ 
    rosdep init && \
    rosdep update && \
    vcs import src --skip-existing --input src/SMACC2/.github/SMACC2.foxy.repos && \
    rosdep install --ignore-src --from-paths src -y -r --skip-keys="gazebo gazebo-ros gazebo-plugins ros-foxy-gazebo-ros ros-foxy-gazebo-plugins" && \
    colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release

# PX4 
ENV SIM_DEP_WS=/root/workspace/dep/sim_deps
RUN mkdir -p ${SIM_DEP_WS} && cd ${SIM_DEP_WS} && \ 
    git clone https://github.com/PX4/PX4-Autopilot.git --recursive && \
    bash PX4-Autopilot/Tools/setup/ubuntu.sh && \
    cd ${SIM_DEP_WS}/PX4-Autopilot && \
    make px4_sitl

# PX4 Msgs
RUN cd ${COLCON_DEP_WS}/src && \
    git clone -b release/1.14 https://github.com/PX4/px4_msgs.git && \
    cd ${COLCON_DEP_WS} && \ 
    source ${ROS2_PATH}/setup.bash && \
    colcon build --packages-select px4_msgs 

# Cmake v3.20.6 for uXRCE-DDS Agent 
RUN apt install build-essential checkinstall zlib1g-dev libssl-dev -y && \
    cd ${SIM_DEP_WS} && \
    wget https://github.com/Kitware/CMake/releases/download/v3.20.6/cmake-3.20.6.tar.gz && \
    tar -zxvf cmake-3.20.6.tar.gz && \
    cd cmake-3.20.6 && \
    ./bootstrap && \ 
    make 

# uXRCE-DDS Agent
RUN cd ${SIM_DEP_WS} && \
    git clone https://github.com/eProsima/Micro-XRCE-DDS-Agent.git && \
    cd Micro-XRCE-DDS-Agent && \
    mkdir build && \
    cd build && \
    ${SIM_DEP_WS}/cmake-3.20.6/bin/cmake .. && \
    make && \
    make install && \
    ldconfig /usr/local/lib

WORKDIR /root/workspace
