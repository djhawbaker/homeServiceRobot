#!/bin/sh

# Start roscore
xterm -e " source /opt/ros/kinetic/setup.bash; roscore " &
sleep 5

# Launch turtlebot
xterm -e " roslaunch my_robot world.launch;" &
sleep 5

# Launch AMCL
xterm -e " roslaunch my_robot amcl.launch initial_pose_a:=1.5708;" &
sleep 5

# Launch Rviz 
xterm -e " roslaunch my_robot view_navigation.launch;" &
sleep 10

# Launch Add Markers 
xterm -e " rosrun add_markers add_markers;" &
sleep 5

# Launch Pick Objects 
xterm -e " rosrun pick_objects pick_objects;" &
