# include <ros/ros.h>
# include "husky_highlevel_controller/nav_space_laser.h"
# include <sensor_msgs/LaserScan.h>
# include <geometry_msgs/Twist.h>
# include <std_msgs/String.h>

sensor_msgs::LaserScan g_scan;
bool ready_flag = false;

void update_global_scan(sensor_msgs::LaserScan f_scan){
	g_scan = f_scan;
	ready_flag = true;
	ROS_INFO_STREAM("G_Scan updated, Size: " << g_scan.ranges.size());
}

int main(int argc,char **argv){

	ros::init(argc,argv,"nav_space_laser_client");
	ros::NodeHandle nh;
	ros::ServiceClient client = nh.serviceClient<husky_highlevel_controller::nav_space_laser>("nav_space_laser");
	husky_highlevel_controller::nav_space_laser service;

	ros::Subscriber subscriber = nh.subscribe("/scan",1,update_global_scan);
	ros::Publisher publisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1,true);
	ros::Publisher talker = nh.advertise<std_msgs::String>("talkie",1,true);




	//Publish Response
	geometry_msgs::Twist msg;


	std_msgs::String chat;
	chat.data = "Hello Topics!";


	while(true & ros::ok()){
	if(ready_flag){

	// Service Call
	service.request.scan = g_scan;
	if(client.call(service)){
	ROS_INFO("Received Destination Target!");
	ROS_INFO_STREAM("x:" << service.response.heading_and_distance.linear.x);
	}else{
	ROS_INFO("Err:: nav_space_laser service call Failed!");
	return 1;
	}
	msg = service.response.heading_and_distance;
	publisher.publish(msg);
	talker.publish(chat);
	ROS_INFO("Published!");
	//ros::spin();
	ready_flag = false;
	}
	ros::spinOnce();
	}
	ros::Duration(1).sleep(); // sleep for 2 seconds
	ROS_INFO("Terminating Node");
	return 0;
}
