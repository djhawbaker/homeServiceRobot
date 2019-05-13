#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"


class Marker : visualization_msgs::Marker {
  public:
    Marker();
    void setMarkerPose(geometry_msgs::Pose pose);
    geometry_msgs::Pose getMarkerPose();
    void publishMarker();

    /* Make an equal overloaded operator for the pose 
bool operator ==() {
    }
*/

  private:
    //visualization_msgs::Marker marker;
    ros::Publisher marker_pub;
};

