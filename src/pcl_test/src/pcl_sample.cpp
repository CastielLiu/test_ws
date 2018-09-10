#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>

int main(int argc,char **argv)
{
	ros::init(argc,argv,"pcl_sample");
	ros::NodeHandle nh;
	ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2>("pcl_output",1);
	
	sensor_msgs::PointCloud2 output;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	
	cloud->width =100;
	cloud->height =1;
	cloud->points.resize(cloud->width*cloud->height);
	
	
	
	
	ros::Rate loop_rate(1);
	
	while(ros::ok())
	{
		for(size_t i=0;i<cloud->points.size();i++)
		{
			cloud->points[i].x = 1024 *rand()/(RAND_MAX+1.0);
			cloud->points[i].y = 1024 *rand()/(RAND_MAX+1.0);
			cloud->points[i].z = 1024 *rand()/(RAND_MAX+1.0);
		}
		pcl::toROSMsg(*cloud,output);
		
		output.header.frame_id = "odom";
		
		pcl_pub.publish(output);
		
		std::cout<<RAND_MAX<< std::endl;
	
		ros::spinOnce();
		
		loop_rate.sleep();
	}
	
	
	
	return 0;
	
}
