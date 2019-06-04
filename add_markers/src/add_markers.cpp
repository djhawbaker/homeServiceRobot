#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include "../include/marker.h"
#include "add_markers/AddMarker.h"
#include "add_markers/RemoveMarker.h"

//static Marker current_marker;
bool found_marker;
ros::Publisher marker_pub;
visualization_msgs::Marker marker;

void odom_callback( const nav_msgs::Odometry odom )
{
  if ( odom.pose.pose.position.x == marker.pose.position.x &&
       odom.pose.pose.position.y == marker.pose.position.x )
  {
    // Found the marker
    found_marker = true;
    ROS_INFO("Found the marker");
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
}

bool handle_remove_marker_request(add_markers::AddMarker::Request& req, add_markers::AddMarker::Response& res)
{
  ROS_INFO("Remove Marker Request received");

  marker.action = visualization_msgs::Marker::DELETE;
  marker_pub.publish(marker);
}

int main( int argc, char** argv )
{
  found_marker = false;

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

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
