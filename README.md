# AEROLOGIC

## Overview

AErial Routing and Operational LOGistics Integration Code

For a deeper understanding of the underlying concepts and terminology used in this project, please refer to the [ROS 2 documentation](https://docs.ros.org/en/rolling/Concepts.html), [SMACC documentation](https://smacc.dev/intro-to-substate-objects/), and the [PX4 ROS 2 user guide](https://docs.px4.io/main/en/ros/ros2_comm.html). Check out the [example state machine branch](https://github.com/ERAU-SUAS/aerologic/tree/sm_example) for a basic state machine implementation.

## Prerequisites

-   [Docker](https://docker.com)

## Installation and Setup

1. Build the image and start the container

```sh
docker-compose up -d --build
```

2. Enter the container

```sh
docker exec -it aerologic bash
```

**note:** Source the following environments before running any ros or build related commands

```sh
source /opt/ros/foxy/setup.bash
source ~/workspace/dep/ros_deps/install/setup.bash
source ~/workspace/dev/install/setup.bash
```

3. Build packages in the `dev` workspace

```sh
cd ~/workspace/dev
colcon build
```

4. Exit and stop the container

```sh
exit
docker-compose down
```

## Running the Simulation

1. Start the uXRCE-DDS agent with the following settings

```sh
MicroXRCEAgent udp4 -p 8888
```

2. In a new terminal session (inside the container), start a gazebo classic simulation

```sh
cd /root/workspace/dep/sim_deps/PX4-Autopilot
make px4_sitl gazebo-classic
```

3. In a new terminal session, run the temporary preflight test node

```sh
source /opt/ros/foxy/setup.bash
source /root/workspace/dev/install/setup.bash
ros2 run sm_uas preflight_ok
```

4. In a new terminal session, run the state machine

```sh
source /opt/ros/foxy/setup.bash
source /root/workspace/dev/install/setup.bash
source /root/workspace/dep/ros_deps/install/setup.bash
ros2 run sm_uas sm_uas_node
```

## Display Forwarding

The following steps were followed on Ubuntu 22.04.

1. Install X11 server host if it's not already installed.

```sh
sudo apt install xorg
```

2. Allow docker container to connect to host's X11 server.

```sh
xhost +local:docker
```

3. Uncomment the following lines in `docker-compose.yml` 

```yml
volumes:
    - /tmp/.X11-unix:/tmp/.X11-unix
environment:
    - DISPLAY=${DISPLAY}
network_mode: "host"
ipc: "host"
```

## Development Guidelines

This project follows the [SMACC2 naming conventions](https://smacc.dev/naming-convention/) to ensure consistency and readability throughout the codebase.

## Resources

### PX4
PX4 is an autopiolot software stack for unmanned aerial vehicles. 

- **PX4 ROS 2 User Guide:** https://docs.px4.io/main/en/ros/ros2_comm.html
- **uORB Message Reference:** https://docs.px4.io/main/en/msg_docs/ 

### SMACC (State Machine Asynchronous C++)

SMACC is a library designed for building complex, high-performance state machines using the ROS framework. It provides a structured way to control behaviors and responses in different scenarios. I _highly_ recommend watching the presentation.

-   **Documentation:** https://smacc.dev/
-   **Presentation:** https://www.youtube.com/watch?v=y6BAqDmHEwA&t=147s
-   **Podcast Interview/Explanation:** https://www.youtube.com/watch?v=3ju1g6g51ss
-   **Source Code:** https://github.com/robosoft-ai/SMACC2

### ROS (Robot Operating System)

ROS is a flexible framework for writing robot software. It's a collection of tools, libraries, and conventions aimed at simplifying the development of complex robotic behaviors.
