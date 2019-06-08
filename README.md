# Home Service Robot 
Robo Nano Degree: Final project. Robot to navigate a home

This project is to build a robot that will map and navigate an environment with specific waypoints.

### To run, setup a terminal and run the following
1. cd catkin_ws
2. catkin_make
3. source devel/setup.bash
4. cd src/homeServiceRobot/scripts
5. ./home_service.sh

## What it does

The Home Service Robot navigates through an environment to pick up markers and take them back to a home base. 

The robot is loaded in the environment and the pick objects node selects where the marker should be. It communicates that to the add_markers node that creates the marker and the AMCL node that handles the path planning to navigate to the marker. 
The robot then navigates to the marker and simulates picking it up in a 5 second processess. 
Once the marker has been retrieved a drop off zone is communicated to the robot by the pick_objects node. 
Once the robot reaches that location the marker is placed delivered and the robot can go on to the next task.


## How it works
This skid steer style robot was defined through a URDF model and the environment was created using the Gazebo build environment tools.

### Localization
Adaptive Monte Carlo Localization (AMCL) is used to continuously determine where the robot is in the environment.
It works by taking sensor inputs and calculating the probability of the robot's state for each particle in a particle cloud. As the robot moves, each particle gets updated with more probable positioning data until it converges and the robot knows with a high probability where it is on the map. 

### Mapping
Simultaneous Localization And Mapping (SLAM) was used to map the environment that the robot is navigating in.
This current environment was mapped already, so SLAM won't need to be run while navigating to collect the markers. 
If mapping did need to occur again due to the environemnt changing we could do this by running 
test_slam.sh 
and having the robot navigate around the environemnt to map it, either through setting goal positions or manually teleoperating the robot.

### Path Planning
Dijkstra's algorithm is used to find the shortest path from the start node to the goal node. It is a complete and optimal solution.
It works by generating nodes to fill the environment with nodes that have a cost to travel to them. If a node is found to be in an obstacle it will be removed. Connections are made between the nodes and assigned a cost to travel that distance. 
The algorithm expands from the start node to it's nearest neighbors following the lowest cost path until it finds a path to the goal. This is a breadth first search style algorithm that will find a path to the goal if there is one. It isn't the most efficient model, but it is guaranteed to find the optimal path to the goal if it exists.
In this case the cost to between each node is the distance to travel because the environment is flat and consistent. 

### Markers
The pick_objects node decides where the goal should be placed and tells the add_markers node to create it. It also provides the goal position to the AMCL node that is handling the path planning. 
