#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "assignment_2_2022/Info.h"

float x;
float y;
float vel_x;
float vel_z;

void odomCallback(const nav_msgs::Odometry::ConstPtr &msg)
{
    x = msg->pose.pose.position.x;
    y = msg->pose.pose.position.y;
    vel_x = msg->twist.twist.linear.x;
    vel_z = msg->twist.twist.angular.z;

    ROS_INFO("[Pos x: %f], [Pos y: %f], [Linear vel: %f], [Angular vel: %f]",
             x, y, vel_x, vel_z);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "msg_node");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/odom", 1, odomCallback);
    ros::Publisher pub_msg = nh.advertise<assignment_2_2022::Info>("/robot_info", 1);

    ros::Rate rate(1);

    while (ros::ok())
    {
        assignment_2_2022::Info new_info;
        new_info.x = x;
        new_info.y = y;
        new_info.vel_x = vel_x;
        new_info.vel_z = vel_z;

        pub_msg.publish(new_info);

        ros::spinOnce();
        rate.sleep();
    }
}