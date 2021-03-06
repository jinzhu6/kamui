#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sh2interface/sh2_tx.h"
#include "std_msgs/Int16.h"

#include <sstream>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "sh2_tx_test");	// 第３引数がnode名

	ros::NodeHandle n;	// nodeへのハンドラ

	ros::Publisher pub = n.advertise<sh2interface::sh2_tx>("sh2_tx", 1000);

	ros::Rate loop_rate(10);	// ループ頻度を設定(10 Hz)

	while (ros::ok())
	{
		sh2interface::sh2_tx msg;
		
		msg.command = 0x13;
		msg.id = 0x01;
		msg.data[0] = 0x0c;
		msg.data[1] = 0xcc;
		msg.data[2] = 0x00;
		msg.data[3] = 0x00;

		pub.publish(msg);

		ros::spinOnce();

		loop_rate.sleep();
	}
}
