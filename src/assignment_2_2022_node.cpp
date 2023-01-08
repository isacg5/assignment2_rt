#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <assignment_2_2022/PlanningAction.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int i_x, i_y;
int cancel_goal = 0;
int goal_stablished = 0;

void get_user_input()
{
	// Ask the user for the goal position or to cancel the goal
	goal_stablished = 0;
	string user_x, user_y;
	cout << "Enter goal introducing 'x' position or enter 'c' to cancel de goal: ";
	cin >> user_x;

	// If the argument introduced is a number, ask for the second coordinate
	try
	{
		i_x = stoi(user_x);
		cout << "Enter goal introducing 'y' position: ";
		goal_stablished = 1;
	}
	// If not, check if is a c to cancel the goal
	catch (invalid_argument const &e)
	{
		if ((user_x.compare("c")) == 0)
		{
			cancel_goal = 1;
			ROS_INFO("Cancelling goal...");
		}
	}

	if (goal_stablished == 1)
	{
		cin >> user_y;
		goal_stablished = 0;
		try
		{
			i_y = stoi(user_y);
			goal_stablished = 1;
		}
		catch (invalid_argument const &e)
		{
		}
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "action_node");

	actionlib::SimpleActionClient<assignment_2_2022::PlanningAction> ac("/reaching_goal", true);

	ac.waitForServer(); // wait for the action server to start

	ros::Rate rate(1);

	while (ros::ok())
	{
		get_user_input();

		// If goal was entered, send the new goal to the action client
		if (goal_stablished == 1)
		{
			ROS_INFO("Action server started, sending goal (%i,%i).", i_x, i_y);
			// send a goal to the action
			assignment_2_2022::PlanningGoal goal;
			goal.target_pose.pose.position.x = i_x;
			goal.target_pose.pose.position.y = i_y;
			goal.target_pose.pose.position.z = 0;
			ac.sendGoal(goal);
		}

		// If goal was cancelled, send cancel to the action client
		if (cancel_goal == 1)
		{
			cancel_goal = 0;
			ac.cancelGoal();
			ROS_INFO("Goal has been cancelled");
		}

		ros::spinOnce();
		rate.sleep();
	}
	return 0;
}
