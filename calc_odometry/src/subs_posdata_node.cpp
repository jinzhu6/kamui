#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include "calc_odometry/posdata.h"
#include "nav_msgs/Odometry.h"
#include <tf/transform_broadcaster.h>

void posCallback(const calc_odometry::posdata::ConstPtr& msg)
{
	//ROS_INFO("x: %f  y: %f  z: %f", msg->x, msg->y, msg->z);
	//ROS_INFO("[pos]  roll: %f  pitch: %f  yaw: %f", msg->roll, msg->pitch, msg->yaw);
	ROS_INFO("flipperFR: %f  flipperFL: %f", msg->flipperFR, msg->flipperFL);
	//ROS_INFO("vx: %f  vy: %f  vz: %f", msg->vx, msg->vy, msg->vz);
	//ROS_INFO("vflipperFR: %f  vflipperFL: %f", msg->vflipperFR, msg->vflipperFL);

	//ROS_INFO("[pos]  yaw: %f", msg->yaw);
}

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  	//x = msg->pose.pose.position.x;
	//y = msg->pose.pose.position.y;
	//z = msg->pose.pose.position.z;

	double roll, pitch, yaw;
	tf::Quaternion q;
	tf::quaternionMsgToTF(msg->pose.pose.orientation, q);
	tf::Matrix3x3(q).getRPY(roll, pitch, yaw);

	//ROS_INFO("[odom] roll: %f  pitch: %f  yaw: %f", roll, pitch, yaw);
	//ROS_INFO("[odom] yaw: %f", yaw);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "subs_posdata_node");

	ros::NodeHandle n;

	ros::Subscriber pos_sub = n.subscribe("robot_pos", 1000, posCallback);
	ros::Subscriber odom_sub = n.subscribe("odom", 1000, odomCallback);
n.advertise<nav_msgs::Odometry>("odom", 1000);

	ros::spin(); // ループ　メッセージが来るのを待つ

	return 0;
}
