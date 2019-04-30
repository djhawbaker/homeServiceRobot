#!/bin/sh
# Launch turtlebot_world.launch
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 1

# Launch AMCL demo to localize the turtlebot 
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch " &
          #roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 1

# Launch Rvix
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 1
