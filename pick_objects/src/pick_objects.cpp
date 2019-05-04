#include <ros/ros.h>
#include "ros/time.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

move_base_msgs::MoveBaseGoal set_goal (double x, double y) {	
  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.orientation.w = y;

  return goal;
}

// Send goals to the program one coordinate at a time with spaces x y message x y message...
int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  //for (int i = 1; i <= argc; i++)
  //{
    move_base_msgs::MoveBaseGoal goal;
    //goal = set_goal(*argv[i], *argv[++i]);
    goal = set_goal(0.0, 10.0);

     // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      //ROS_INFO(argv[++i]);
      ROS_INFO("Hooray, reached the goal");
    }
    else
    {
      ROS_INFO("The base failed to move to the goal for some reason");
    }

    // Wait for 5 seconds before going to the next location
    ros::Duration(5, 0).sleep();
  //}

  return 0;
}
