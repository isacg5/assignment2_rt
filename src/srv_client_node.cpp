#include "ros/ros.h"
#include "assignment_2_2022/Goals.h"
#include <assignment_2_2022/PlanningAction.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "service_node");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<assignment_2_2022::Goals>("/goals");

    ros::Rate rate(1);

    assignment_2_2022::Goals server_result;

    while (ros::ok())
    {
        // Print the number of goals reached and cancelled obtained through the service /goals
        client.call(server_result);
        ROS_INFO("[REACHED: %i] [CANCELLED: %i]", server_result.response.reached, server_result.response.cancelled);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
