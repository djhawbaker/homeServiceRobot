#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Orientation.h"


class Marker (){
  public:
    void Marker();
    void setMarkerPose(geometry_msgs::Pose pose);
    geometry_msgs::Pose getMarkerPose();
    void publishMarker();


  private:
    visualization_msgs::Marker marker;
    ros::Publisher marker_pub;
};

