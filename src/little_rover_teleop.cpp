#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class LittleRoverTeleop
{
public:
  LittleRoverTeleop();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};


LittleRoverTeleop::LittleRoverTeleop():
  linear_(5),
  angular_(2),
  l_scale_(5),
  a_scale_(5)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("little_rover/mobile_base_controller/cmd_vel", 50);


  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 50, &LittleRoverTeleop::joyCallback, this);

}

void LittleRoverTeleop::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  twist.angular.z = a_scale_*(long long int)joy->axes[angular_];
  twist.linear.x = l_scale_*(long long int)joy->axes[linear_];
  vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "little_rover_teleop");
  LittleRoverTeleop littleRoverTeleop;

  ros::spin();
}
