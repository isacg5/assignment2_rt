#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <assignment_2_2022/PlanningAction.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "action_node");
	
	actionlib::SimpleActionClient<assignment_2_2022::PlanningAction> ac("/reaching_goal", true);

	int user_x, user_y;
	cout << "Enter goal following the format 'x' 'y': ";
	cin >> user_x;
	cin >> user_y;

	ac.waitForServer(); // wait for the action server to start
	ROS_INFO("Action server started, sending goal (%i,%i).", user_x, user_y);
	
	// send a goal to the action
	assignment_2_2022::PlanningGoal goal;
	goal.target_pose.pose.position.x = user_x;
	goal.target_pose.pose.position.y = user_y;
	goal.target_pose.pose.position.z = 0;
	ac.sendGoal(goal);

	// wait for the action to return
	bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

	if (finished_before_timeout)
	{
		actionlib::SimpleClientGoalState state = ac.getState();
		ROS_INFO("Action finished: %s", state.toString().c_str());
	}
	else
	{
		ROS_INFO("Action did not finish before the time out.");
		ac.cancelGoal();
		ROS_INFO("Goal has been cancelled");
	}

	ros::Rate rate(1);

	while (ros::ok())
	{
		ros::spinOnce();
		rate.sleep();
	}
	return 0;
}
