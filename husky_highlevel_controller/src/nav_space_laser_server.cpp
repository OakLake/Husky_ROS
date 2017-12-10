# include <ros/ros.h>
# include "husky_highlevel_controller/nav_space_laser.h"
# include <sensor_msgs/LaserScan.h>
# include <geometry_msgs/Twist.h>

bool compass(husky_highlevel_controller::nav_space_laser::Request &request,husky_highlevel_controller::nav_space_laser::Response &response){
	float max = 0;
	float ang = 0;
	int ang_max_ix = 0;	
	for (int i=0;i<request.scan.ranges.size();i++){
	if(request.scan.ranges[i] > max){
		max = request.scan.ranges[i];
		ang_max_ix = i;
	}
	}
	float heading = request.scan.angle_min + ang_max_ix*request.scan.angle_increment;
	float distance = 0.5*max;

	response.heading_and_distance.linear.x = distance;
	response.heading_and_distance.linear.y = 0;
	response.heading_and_distance.linear.z = 0;
	response.heading_and_distance.angular.x = 0;
	response.heading_and_distance.angular.y = 0;
	response.heading_and_distance.angular.z = -heading;

	return true;
}


int main(int argc, char **argv){
	ros::init(argc,argv,"nav_space_laser_server");
	ros::NodeHandle nh;
	ros::ServiceServer service = nh.advertiseService("nav_space_laser",compass);
	ros::spin();
	return 0;
}
