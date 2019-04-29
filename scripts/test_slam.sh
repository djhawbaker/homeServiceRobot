#!/bin/sh
# Start roscore
xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" &
sleep 5

# Launch turtlebot_world.launch
xterm -e " roslaunch turtlebot_simulator turtlebot_world.launch " &
sleep 1

# Launch Gmapping demo or slam Gmapping to perform SLAM
xterm -e " roslaunch turtlebot_simulator gmapping_demo.launch " &
sleep 1

# Launch Rvix
xterm -e " roslaunch turtlebot_interactions view_navigation.launch " &
sleep 1

# Launch teleop keyboard
xterm -e " roslaunch turtlebot keyboard_teleop.launch " &
