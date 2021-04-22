#include <ros/ros.h>
#include <sensor_msgs/Joy.h>


void callback(const sensor_msgs::Joy::ConstPtr& msg)
{
	ROS_INFO("%f", msg->axes[3]);
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "little_rover_teleop");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("/joy", 1000, callback);
	ros::spin();
	return 0;
}
