
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Orientation.h"
#include "marker.h"

static Marker current_marker;
bool found_marker;

void odom_callback( const nav_msgs::Odometry odom )
{
  if (current_marker.marker.pose == odom.pose )
  {
    found_marker = true;
    ROS_INFO("Found the marker");
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
  ros::Subscriber marker = n.subscribe("visualization_marker", 10, marker_callback);
 
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  //while (ros::ok())
  while (ros::ok())
  {
    visualization_msgs::Marker marker;

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
    current_marker.publishMarker();
    //marker_pub.publish(marker);

    if (found_marker)
    {
        // If robot has reached the pick up zone, delete it
        current_marker.marker.action = visualization_msgs::Marker::DELETE;
        current_marker.publishMarker();
        //marker_pub.publish(current_marker.marker);
      
        found_marker = false;
        // Wait 5 seconds to simulate the "pick up"
        sleep(5);

        // Then move the marker to the drop off zone
        geometry_msgs::Pose pose;
        pose.position.x = 0.0;
        pose.position.x = 0.0;
        pose.position.x = 0.0;
        pose.orientation.x = 0.0;
        pose.orientation.y = 0.0;
        pose.orientation.z = 0.0;
        pose.orientation.w = 0.0;
        
        current_marker.marker.action = visualization_msgs::Marker::ADD;
        current_marker.marker.setMarkerPose(pose);
        current_marker.publishMarker();
        //marker_pub.publish(current_marker.marker);
    }
  }
}
