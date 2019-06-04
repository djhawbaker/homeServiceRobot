#!/bin/sh
# Launch turtlebot_world.launch
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch; bash " &
sleep 5

# Launch AMCL demo to localize the turtlebot 
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch; bash " &
          #roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 5

# Launch Rvix
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch; bash " &
