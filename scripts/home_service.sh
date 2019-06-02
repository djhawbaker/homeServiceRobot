#!/bin/sh

# Start roscore
xterm -e " source /opt/ros/kinetic/setup.bash; roscore " &
sleep 5

# Launch turtlebot
xterm -e " roslaunch my_robot world.launch; bash " &
sleep 1

# Launch AMCL
#xterm -e " roslaunch my_robot amcl.launch; bash " &
xterm -e " roslaunch my_robot localization.launch; bash " &
sleep 5

# Launch Rviz
xterm -e " roslaunch my_robot view_navigation.launch; bash " &
sleep 5

# Launch Add Markers 
xterm -e " rosrun add_markers add_markers; bash " &
sleep 5

# Launch Pick Markers
#xterm -e " export ROS_IP=`hostname -I`; rosrun pick_objects pick_objects; bash " &
xterm -e " rosrun pick_objects pick_objects; bash " &
