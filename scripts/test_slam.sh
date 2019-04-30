#!/bin/sh
# Start roscore
xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" &
sleep 5

# Launch turtlebot_world.launch
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 1

# Launch Gmapping demo or slam Gmapping to perform SLAM
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 1

# Launch Rvix
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 1

# Launch teleop keyboard
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch " &
