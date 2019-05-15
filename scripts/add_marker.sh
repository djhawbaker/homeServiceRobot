#!/bin/sh

# Start roscore
xterm -e " source /opt/ros/kinetic/setup.bash; roscore " &
sleep 5

# Launch turtlebot
xterm -e " roslaunch my_robot world.launch;bash " &
sleep 1

# Launch AMCL
xterm -e " roslaunch my_robot amcl.launch;bash " &
sleep 1

# Launch Rviz
xterm -e " roslaunch my_robot view_navigation.launch;bash " &
sleep 5

# Launch Add Markers 
xterm -e " rosrun add_markers add_markers;bash " &
