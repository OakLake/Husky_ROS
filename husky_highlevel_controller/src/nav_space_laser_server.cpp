# include <ros/ros.h>
# include "husky_highlevel_controller/nav_space_laser.h"
# include <sensor_msgs/LaserScan.h>
# include <geometry_msgs/Twist.h>
//# include <assert.h>

bool compass(husky_highlevel_controller::nav_space_laser::Request &request,husky_highlevel_controller::nav_space_laser::Response &response){

	sensor_msgs::LaserScan lsr;
	lsr = request.scan;

	//assert(lsr.ranges.size() > 0);
	ROS_INFO_STREAM("Service DEBUG: size: "<< lsr.ranges.size());


	float max = -1;
	float ang = 0;
	int ang_max_ix = 0;
	for (int i=0;i<lsr.ranges.size();i++){
	if(lsr.ranges[i] > max){
		max = lsr.ranges[i];
		ang_max_ix = i;
	}
	}
	float heading = 0.7*(lsr.angle_min + ang_max_ix*lsr.angle_increment);
	float distance = 0.5*max;

	response.heading_and_distance.linear.x = distance;
	response.heading_and_distance.linear.y = 0.0;
	response.heading_and_distance.linear.z = 0.0;
	response.heading_and_distance.angular.x = 0.0;
	response.heading_and_distance.angular.y = 0.0;
	response.heading_and_distance.angular.z = -heading;
	ROS_INFO_STREAM("Service:> x: " << distance <<" Heading: " << -heading);
	return true;
}


int main(int argc, char **argv){
	ros::init(argc,argv,"nav_space_laser_server");
	ros::NodeHandle nh;
	ros::ServiceServer service = nh.advertiseService("nav_space_laser",compass);
	ros::spin();
	return 0;
}
