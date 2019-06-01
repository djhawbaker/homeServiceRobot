#include <ros/ros.h>
#include "ros/time.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "add_markers/AddMarker.h"
#include "add_markers/RemoveMarker.h"

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
// Define a global client that can request services
ros::ServiceClient client_add;
ros::ServiceClient client_remove;

bool send_goal(float x, float y, float w) {
  // Send the goal to move to and wait for the robot to reach it

  //tell the action client that we want to spin a thread by default
  // TODO should it be move_base or robot_footprint?
  MoveBaseClient ac("move_base", true);
 // MoveBaseClient ac("robot_footprint", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = w;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal, X: %f, Y: %f, W: %f", x, y, w);
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Hooray, the base moved to the goal! X: %f, Y: %f, W: %f", x, y, w);
    return true;
  }
  else
  {
    ROS_INFO("The base failed to move to the goal. X: %f, Y: %f, W: %f Figure out why", x, y, w);
    return false;
  }
}


void add_marker(float x, float y) {
  // Add the marker to the map
  add_markers::AddMarker srv;

  srv.request.xPos = x;
  srv.request.yPos = y;

  if ( !client_add.call(srv) ) {
    ROS_ERROR( "Failed to call add_markers Add Marker service" );
  }

}

void remove_marker() {
  // Remove the marker to the map, it's been picked up
  add_markers::RemoveMarker srv;

  if ( !client_remove.call(srv) ) {
    ROS_ERROR( "Failed to call add_markers Remove Marker service" );
  }
}

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  
  ros::NodeHandle nh;
  ros::ServiceClient client_add = nh.serviceClient<add_markers::AddMarker>("AddMarker");
  ros::ServiceClient client_remove = nh.serviceClient<add_markers::RemoveMarker>("RemoveMarker");


  // Add the initial marker
  add_marker(5.0, 0.0);

  // Tell the robot where the goal is
  if (send_goal(5.0, 0.0, 0.0)) {
    // Made it to the marker, remove it
    remove_marker();
    // Wait for 5 seconds
    sleep(5);
  }

  ROS_INFO("Sending goal to get home");

  add_marker(0.0, 0.0);

  if (send_goal(0.0, 0.0, 0.0)) {
    // Made it to the marker, remove it
    remove_marker();
  }

  return 0;
}
