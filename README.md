# Husky_ROS

Based on ETH-Zürich "Programming for Robotics - ROS", with personal additions for exploring ROS ecosystem.

Course Link:<br/>
http://www.rsl.ethz.ch/education-students/lectures/ros.html

Youtube:<br/>
https://www.youtube.com/playlist?list=PLE-BQwvVGf8HOvwXPgtDfWoxd4Cc6ghiP


--------------------

### Launch Files:
- husky_HLC       : husky on Gazebo and Rviz with 'autonomous' navigation to pillar object.
- husky_SLAM : husky with teleop and ROS gmapping.
- husky_SLAM_KinSen : husky_SLAM with Kinect Sensor enabled(not used);


--------------------

### Nodes:
- nav_space_laser_client: subscribes to '/scan' and uses the service 'nav_space_laser' to publish a '/cmd_vel' message, robot will head in the direction of largest laser scan reading, for test purposes Only!.
