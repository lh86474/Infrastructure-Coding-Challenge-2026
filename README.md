# Infrastructure-Coding-Challenge-2026

## What my program does

I have an adder node that subscribes to two inputs (first topics) and publishes one output (3rd topic).

I have two callback functions, one for each input topic. The adder function adds the two inputs and 
gives the final output. I used rclcpp for this program. 

## Commands needed to run and build the program

### Building the image and running the container

`export ROS_VERSION=$(curl -s https://api.github.com/repos/ros-infrastructure/ros-apt-source/releases/latest | grep -F "tag_name" | awk -F'"' '{print $4}')`

This command was used to fetch the ROS apt source version per the ros2 humble
installation instructions. 

`docker build --build-arg ROS_APT_SOURCE_VERSION=$ROS_VERSION -t my-image .`

I decided to call the image my-image, you can call it whatever you want. 

Builds the container with --build-arg from our export. 

`docker run --rm -it --mount type=bind,source="<path to project>",target=/work my-image bash`

Runs the container. I had to use a bind mount so I could use my cloned
repository inside the container. 

`colcon build`

Run this in the workspace root to build the workspace, which is in `/work/ros2_ws`. 

### Running the node

My Dockerfile takes care of sourcing ROS Humble, but we have to source our built workspace

```
source /work/ros2_ws/install/setup.bash
ros2 run infra_coding_challenge_package adder_node
```

Use to run the node.

In **another terminal** (there will be three running at once), run these commands

```
docker exec -it <container_id> bash
source /work/ros2_ws/install/setup.bash
ros2 topic echo /output_topic
```

This terminal displays the published sums.

In **the third terminal**, run the ros2 topic pub commands

```
docker exec -it <container_id> bash
source /work/ros2_ws/install/setup.bash
ros2 topic pub --once /input_topic_a std_msgs/msg/Float64 "{data: <float number>}"
ros2 topic pub --once /input_topic_b std_msgs/msg/Float64 "{data: <float number>}"
```

## ros2 topic pub commands

`ros2 topic pub --once /input_topic_a std_msgs/msg/Float64 "{data: 3.0}"`

Set `input_topic_a` to 3.0

`ros2 topic pub --once /input_topic_b std_msgs/msg/Float64 "{data: 4.0}"`

Set `input_topic_b` to 4.0

The sum of the two commands should show data: 7.0 in the terminal that is running

`ros2 topic echo /output_topic`

## Screenshots

