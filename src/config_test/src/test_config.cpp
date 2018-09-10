#include "ros/ros.h"
#include <dynamic_reconfigure/server.h>
#include<std_msgs/String.h>
#include<config_test/test_Config.h>   //packageName/..
#include<opencv2/opencv.hpp>

using namespace std;

void  test_callback(config_test::test_Config &config,uint32_t level)
{
	ROS_INFO("Reconfigure Request:%d %f %s %s %d",
			config.int_param,
			config.double_param,
			config.str_param.c_str(),
			config.bool_param?"TRUE":"FALSE",
			config.size);
}

int main(int argc,char**argv)
{
	ros::init(argc,argv,"test_cfg_node");
	dynamic_reconfigure::Server<config_test::test_Config>server;
	
	dynamic_reconfigure::Server<config_test::test_Config>::CallbackType f;
	
	f = boost::bind(&test_callback,_1,_2);
	server.setCallback(f);
	

	ros::NodeHandle n;
	
	//ros::Subscriber sub = n.subscribe("/clock",100,callback);  //vertical_laser_2d  //
	cv::VideoCapture capture(0);
	cv::Mat image;
	
	while(1)
	{
		capture >> image;
		
		if(image.empty())
			continue;
			
		cv :: imshow("Image",image);
		
		cv::waitKey(30);
		
		ros::spin();
	
	}
	
	

	return 0;
}
