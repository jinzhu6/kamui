#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "sensor_msgs/Range.h"
#include "math.h"
#include "thermo_blob/blob.h"

//=======================================================================================================//
//ThermoRangeクラス
//=======================================================================================================//
class ThermoRange
{
public:

	ThermoRange(){
		ros::NodeHandle n;
		sub_blob = n.subscribe("optris/ThermoBlob", 1000, &ThermoRange::thermoCallback, this);
		pub_range = n.advertise<sensor_msgs::Range>("range", 1000);
	}
	
	~ThermoRange(){};

	void thermoCallback(const std_msgs::Bool::ConstPtr& msg)	// 熱画像処理が行われたタイミングでrangeデータ配信
	{
		double range0, view0;
		range.header.frame_id = "/thermocam_link";
		if(ros::param::has("/thermo_range_node/field_of_view"))
		{
			ros::param::get("/thermo_range_node/field_of_view", view0);
			range.field_of_view = view0*M_PI/180;
		}
		else
		{
			range.field_of_view = 40*M_PI/180;
		}
		if(ros::param::has("/thermo_range_node/range"))
		{
			ros::param::get("/thermo_range_node/range", range0);
			range.range = range0;
			range.min_range = range0;
			range.max_range = range0;
		}
		else
		{
			range.range = 0.4;
			range.min_range = 0.4;
			range.max_range = 0.4;
		}

		pub_range.publish(range);
	}

private:
	ros::Subscriber sub_blob;
	ros::Publisher pub_range;
	sensor_msgs::Range range;
};

int main(int argc, char **argv)
{
	ros::init(argc, argv, "thermo_range_node");

	ThermoRange thr;

	ros::spin();
}
