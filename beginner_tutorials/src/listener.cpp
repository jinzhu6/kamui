#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include "nav_msgs/OccupancyGrid.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("I heard: [%s]", msg->data.c_str());
}

void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
	for(int i=0; i<10; i++)
	{
		ROS_INFO("map data: [%d]", msg->data[i]);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "listener");

	ros::NodeHandle n;

	// chatterのトピックを購読し、新しいメッセージが来るたびにchatterCallbackを呼び出す
	ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
	ros::Subscriber sub_map = n.subscribe("nav_map", 1000, mapCallback);
	

	ros::spin(); // ループ　メッセージが来るのを待つ

	return 0;
}
