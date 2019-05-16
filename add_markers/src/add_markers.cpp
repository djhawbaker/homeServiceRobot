
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include "../include/marker.h"

//static Marker current_marker;
bool found_marker;

void odom_callback( const nav_msgs::Odometry odom )
{
  if ( odom.pose.pose.position.x == 5.0 &&
       odom.pose.pose.position.y == 0.0 &&
       odom.pose.pose.position.z == 0.0)
  {
    // Found the marker
    found_marker = true;
    ROS_INFO("Found the marker");
  }
  if ( found_marker &&
       odom.pose.pose.position.x == 0.0 &&
       odom.pose.pose.position.y == 0.0 &&
       odom.pose.pose.position.z == 0.0)
  {
    // Made it to the drop off zone
    ROS_INFO("Reached the drop off zone");

    // Show the marker at the drop off zone
    visualization_msgs::Marker marker;

    marker.pose.position.x = 0.0;
    marker.pose.position.y = 0.0;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 0.0;
    
    marker.action = visualization_msgs::Marker::ADD;

    ros::NodeHandle n;
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    marker_pub.publish(marker);
  }
}

int main( int argc, char** argv )
{
  found_marker = false;

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  ros::Subscriber odom_sub = n.subscribe("odom", 10, odom_callback);
  //ros::Subscriber marker = n.subscribe("visualization_marker", 10, marker_callback);
 
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
    

  //while (ros::ok())
  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    marker.header.frame_id = "map"; 
    marker.header.stamp = ros::Time::now();

    marker.ns = "basic_shapes";
    marker.id = 0;

    marker.type = shape;
    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = 5.0;
    marker.pose.position.y = 0.0;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 0.0;

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0f;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    //current_marker.publishMarker();
    marker_pub.publish(marker);
    r.sleep();

    if (found_marker)
    {
        // If robot has reached the pick up zone, delete it
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        //marker_pub.publish(current_marker.marker);
      
        //found_marker = false;
        // Wait 5 seconds to simulate the "pick up"
        sleep(5);
  
        // Set the goal as the drop off zone
        // TODO

    }
  }
}
