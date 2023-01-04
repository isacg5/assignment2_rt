#include "ros/ros.h"
#include "assignment_2_2022/Goals.h"
#include <assignment_2_2022/PlanningAction.h>

int counter_reached;
int counter_cancelled;

void subsCallback(const assignment_2_2022::PlanningActionResult::ConstPtr &msg)
{
    int result;
    result = msg->status.status;

    if(result == 3){
        counter_reached += 1;
    }
    else if(result == 2){
        counter_cancelled += 1;
    }
}

bool goalsCallback(assignment_2_2022::Goals::Request &req, assignment_2_2022::Goals::Response &res)
{
    res.reached = counter_reached;
    res.cancelled = counter_cancelled;

    return true;
}

int main(int argc, char **argv)
{
    counter_reached = 0;
    counter_cancelled = 0;

    ros::init(argc, argv, "goals_server");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/reaching_goal/result", 1, subsCallback);
    ros::ServiceServer service = n.advertiseService("/goals", goalsCallback);
    ros::spin();
    
    return 0;
}