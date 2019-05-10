#!/bin/sh

# Start roscore
xterm -e " source /opt/ros/kinetic/setup.bash; roscore " &
sleep 5

# Launch turtlebot
#xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
xterm -e " roslaunch my_robot world.launch;bash " &
sleep 1

# Launch AMCL
xterm -e " roslaunch my_robot amcl.launch;bash " &
sleep 1

# Launch Rviz
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch;bash " &
sleep 5

# Launch Add Markers 
xterm -e " roslaunch add_markers add_markers.launch;bash " &
