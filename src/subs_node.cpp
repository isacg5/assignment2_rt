#include "ros/ros.h"
#include "assignment_2_2022/Info.h"
#include <assignment_2_2022/PlanningAction.h>
#include <math.h>

float current_x;
float current_y;

float goal_x;
float goal_y;

float euclidean_distance;

void goalCallback(const assignment_2_2022::PlanningActionGoal::ConstPtr &msg)
{
    goal_x = msg->goal.target_pose.pose.position.x;
    goal_y = msg->goal.target_pose.pose.position.y;
    ROS_INFO("[goal: %f, %f] ", goal_x, goal_y);
}

void robotInfoCallback(const assignment_2_2022::Info::ConstPtr &msg)
{
    current_x = msg->x;
    current_y = msg->y;
    ROS_INFO("[CURRENT: %f, %f] ", current_x, current_y);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "subs_node");

    // Get the parameter obtained in the launch file for the frequency of execution of the node
    float frequency;
    ros::param::get("/vel_publishing", frequency);

    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/robot_info", 1, robotInfoCallback);
    ros::Subscriber sub_goal = n.subscribe("/reaching_goal/goal", 1, goalCallback);

    goal_x = current_x;
    goal_y = current_y;

    ros::Rate rate(frequency);

    while (ros::ok())
    {
        // Get the euclidean distance between the current position of the robot and the goal, by subscribing to the action clinet and the topic created for the custom message
        int x = goal_x - current_x;
        int y = goal_y - current_y;
        euclidean_distance = sqrt(pow(x, 2) + pow(y, 2));
        ROS_INFO("[DISTANCE: %f] ", euclidean_distance);
        ros::spinOnce();
        rate.sleep();
    }
    return 0;
}
