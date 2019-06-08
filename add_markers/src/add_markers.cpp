#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include "../include/marker.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include "add_markers/AddMarker.h"

bool found_marker;
bool marker_set = false;
ros::Publisher marker_pub;
float MARKER_RADIUS = 0.3;
float MARKER_X_POS = 1000;
float MARKER_Y_POS = 1000;

typedef actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> MoveBaseServer;

void odom_callback( const nav_msgs::Odometry odom )
{
  if ( marker_set &&
       ((MARKER_X_POS - MARKER_RADIUS ) <= odom.pose.pose.position.x )&&
       (odom.pose.pose.position.x <= ( MARKER_X_POS + MARKER_RADIUS )) &&
       (( MARKER_Y_POS - MARKER_RADIUS ) <= odom.pose.pose.position.y) &&
       (odom.pose.pose.position.y <= ( MARKER_Y_POS + MARKER_RADIUS )))
  {
    // Found the marker
    found_marker = true;
    ROS_INFO("Found the marker");

    // Publish that the marker was found
    MoveBaseServer server("move_base", false);
    server.start();
    
    move_base_msgs::MoveBaseResult result;
    server.setSucceeded(result);
  }
}

bool handle_marker_request(add_markers::AddMarker::Request& req, add_markers::AddMarker::Response& res)
{
  if (req.show == true) {
    ROS_INFO("Add Marker Request received - x: %f, y: %f", (float)req.xPos, (float)req.yPos);
    visualization_msgs::Marker marker;
    marker.header.frame_id = "map"; 
    marker.header.stamp = ros::Time::now();

    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker coordinates
    marker.pose.position.x = req.xPos;
    marker.pose.position.y = req.yPos;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    
    // Set the scale
    marker.scale.x = MARKER_RADIUS * 2;
    marker.scale.y = MARKER_RADIUS * 2;
    marker.scale.z = MARKER_RADIUS * 2;

    // Set the color
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0f;

    marker.lifetime = ros::Duration();
    
    marker.action = visualization_msgs::Marker::ADD;
    marker.type = visualization_msgs::Marker::CUBE;

    marker_set = true;
    MARKER_X_POS = req.xPos;
    MARKER_Y_POS = req.yPos;
    marker_pub.publish(marker);
  }
  else{

    ROS_INFO("Remove Marker Request received");

    visualization_msgs::Marker marker;
    marker.ns = "basic_shapes";
    marker.id = 0;

    marker.action = visualization_msgs::Marker::DELETE;
    marker_set = false;
    marker_pub.publish(marker);
  }
}

int main( int argc, char** argv )
{
  found_marker = false;

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  //ros::Rate r(1);
 
  // Setup the communication with other nodes
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("odom", 10, odom_callback);
  ros::ServiceServer addMarkerServer = n.advertiseService("/add_markers/AddMarker", handle_marker_request);
    
  ROS_INFO("Ready to receive Add Marker requests");
  
  // Handle ROS communication events
  ros::spin();

  return 0;
}
