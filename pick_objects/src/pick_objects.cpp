#include <ros/ros.h>
#include "ros/time.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "add_markers/AddMarker.h"
#include "add_markers/RemoveMarker.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
// Define a global client that can request services
ros::ServiceClient client_add;

bool send_goal(float x, float y) {
  // Send the goal to move to and wait for the robot to reach it

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

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
  // Needs a normalized value of 1.0
  goal.target_pose.pose.orientation.w = 1.0;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal, X: %f, Y: %f", x, y);
  ac.sendGoal(goal);

  // Wait 30 seconds for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Hooray, the base moved to the goal! X: %f, Y: %f", x, y);
    return true;
  }
  else
  {
    ROS_INFO("The base failed to move to the goal. X: %f, Y: %f Figure out why", x, y);
    return false;
  }
}


void add_marker(float x, float y) {
  // Add the marker to the map
  add_markers::AddMarker srv;

  srv.request.xPos = x;
  srv.request.yPos = y;
  srv.request.show = true;

  if ( !client_add.call(srv) ) {
    ROS_ERROR( "Failed to call add_markers Add Marker service" );
  }

}

void remove_marker() {
  // Remove the marker to the map, it's been picked up
  add_markers::AddMarker srv;

  srv.request.xPos = 0;
  srv.request.yPos = 0;
  srv.request.show = false;

  if ( !client_add.call(srv) ) {
    ROS_ERROR( "Failed to call add_markers Remove Marker service" );
  }
}

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle nh;
  
  // Create the service Clients to interact with the add_markers node
  client_add = nh.serviceClient<add_markers::AddMarker>("/add_markers/AddMarker");

  // Get goal and home coordinates
  float goal_x = 3.5;
  float goal_y = 2.0;
  float home_x = -1;
  float home_y = -2;

  // Get node name
  std::string node_name = ros::this_node::getName();

  // Add the initial marker
  add_marker(goal_x, goal_y);

  // Tell the robot where the goal is. The robot stays in the 2D ground plane, so z will always be 0
  ROS_INFO("Sending coordinates for the marker location");

  if (send_goal(goal_x, goal_y)) {
    // Made it to the marker, remove it
    remove_marker();
    // Wait for 5 seconds to simulate picking up the marker
    sleep(5);
  }

  ROS_INFO("Sending coordinates for the drop off location");

  if (send_goal(home_x, home_y)) {
    // Made it to the dropoff location, add the marker
    add_marker(home_x, home_y);
  }

  return 0;
}
