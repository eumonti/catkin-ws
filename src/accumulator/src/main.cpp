#include <iostream>
#include <array>

#include <ros/ros.h>
#include <std_msgs/Float64.h>

void data_handler(const std_msgs::Float64::ConstPtr&);

int main(int argc, char **argv) {
    ros::init(argc, argv, "accumulator");

    ros::NodeHandle nh;
    auto _subscriber = nh.subscribe("/data", 50, data_handler);
    ROS_INFO("Hello world\n");
    ros::spin();
}
