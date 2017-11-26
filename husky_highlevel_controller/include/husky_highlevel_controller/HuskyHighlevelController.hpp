#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>

namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class HuskyHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	HuskyHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~HuskyHighlevelController();


private:
	ros::NodeHandle nodeHandle_;
	ros::Subscriber subscriber;
	ros::Publisher publisher;
	ros::Publisher marker_publisher;
	void laser_callback(const sensor_msgs::LaserScan::ConstPtr& lsr_msg);
	float ang_pillar; // in rad
  	float k_dist;
  	float k_ang;
};

} /* namespace */
