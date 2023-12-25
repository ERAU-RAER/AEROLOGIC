# AEROLOGIC

AErial Routing and Operational LOGistics Integration Code

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

**note:** Source the following environments before running any ros related commands

```sh
source /opt/ros/foxy/setup.bash
source ~/workspace/dep/install/setup.bash
source ~/workspace/dev/install/setup.bash
```

5. Exit and stop the container

```sh
exit
docker-compose down
```

## Development Guidelines

### SMACC2 Naming Conventions

This project follows the [SMACC2 naming conventions](https://smacc.dev/naming-convention/) to ensure consistency and readability throughout the codebase.
