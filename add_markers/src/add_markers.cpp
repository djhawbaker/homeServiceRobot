#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include "../include/marker.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include "add_markers/AddMarker.h"
#include "add_markers/RemoveMarker.h"

//static Marker current_marker;
bool found_marker;
bool marker_set = false;
ros::Publisher marker_pub;
//ros::Publisher found_marker_pub;
visualization_msgs::Marker marker;
float MARKER_RADIUS = 0.01;
typedef actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction> MoveBaseServer;

void odom_callback( const nav_msgs::Odometry odom )
{
  //ROS_INFO("Odom callback x: %f, y: %f", marker.pose.position.x, marker.pose.position.y);
  //ROS_INFO("Odom pose : %f, y: %f", odom.pose.pose.position.x, odom.pose.pose.position.y);
  if ( marker_set &&
       ((marker.pose.position.x - MARKER_RADIUS ) <= odom.pose.pose.position.x )&&
       (odom.pose.pose.position.x <= ( marker.pose.position.x + MARKER_RADIUS )) &&
       (( marker.pose.position.y - MARKER_RADIUS ) <= odom.pose.pose.position.y) &&
       (odom.pose.pose.position.y <= ( marker.pose.position.y + MARKER_RADIUS )))
  {
    // Found the marker
    found_marker = true;
    ROS_INFO("Found the marker");

    // Publish that the marker was found
    MoveBaseServer server("move_base", false);
    server.start();
    // Wait 5 sec for move_base action server to come up
    
    move_base_msgs::MoveBaseResult result;
    server.setSucceeded(result);


    /* add_markers::FoundMarker foundMarker;
    foundMarker.FOUND = true;
    found_marker_pub.publish(foundMarker);
    */
  }
}

bool handle_add_marker_request(add_markers::AddMarker::Request& req, add_markers::AddMarker::Response& res)
{
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
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0f;

    marker.lifetime = ros::Duration();
    
    marker.action = visualization_msgs::Marker::ADD;
    marker.type = visualization_msgs::Marker::CUBE;

    marker_pub.publish(marker);
    marker_set = true;
}

bool handle_remove_marker_request(add_markers::AddMarker::Request& req, add_markers::AddMarker::Response& res)
{
  ROS_INFO("Remove Marker Request received");

  marker.action = visualization_msgs::Marker::DELETE;
  marker_set = false;
  marker_pub.publish(marker);
}

int main( int argc, char** argv )
{
  found_marker = false;

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
 
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  //found_marker_pub = n.advertise<add_markers::FoundMarker>("found_marker", 1);

  ros::Subscriber odom_sub = n.subscribe("odom", 10, odom_callback);
  //ros::Subscriber marker = n.subscribe("visualization_marker", 10, marker_callback);
  ros::ServiceServer addMarkerServer = n.advertiseService("/add_markers/AddMarker", handle_add_marker_request);
  ros::ServiceServer removeMarkerServer = n.advertiseService("/add_markers/RemoveMarker", handle_remove_marker_request);
 
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
    
  ROS_INFO("Ready to receive Add Marker requests");
  
  // Handle ROS communication events
  ros::spin();

  return 0;
}
