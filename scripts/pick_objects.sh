#!/bin/sh

# Start roscore
xterm -e " source /opt/ros/kinetic/setup.bash; roscore " &
sleep 5

# Launch turtlebot
#xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
xterm -e " roslaunch my_robot world.launch " &
sleep 1

# Launch AMCL
xterm -e " roslaunch my_robot amcl.launch " &
sleep 1

# Launch Rviz
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5

# Launch Pick Objects
#xterm -e " roslaunch pick_objects pick_objects.launch " &
