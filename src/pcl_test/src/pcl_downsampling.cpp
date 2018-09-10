#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/filters/voxel_grid.h>
#include <dynamic_reconfigure/server.h>
#include <pcl_test/pcl_test_Config.h>

class cloudHandler
{
public:
    cloudHandler()
    {
        pcl_sub = nh.subscribe("pcl_filtered", 10, &cloudHandler::cloudCB, this);
        pcl_pub = nh.advertise<sensor_msgs::PointCloud2>("pcl_downsampled", 1);
        f = boost::bind(&cloudHandler::reconfigureCB,this,_1,_2);
        server.setCallback(f);
    }

    void cloudCB(const sensor_msgs::PointCloud2 &input)
    {
        pcl::PointCloud<pcl::PointXYZ> cloud;
        pcl::PointCloud<pcl::PointXYZ> cloud_downsampled;
        sensor_msgs::PointCloud2 output;

        pcl::fromROSMsg(input, cloud);

        pcl::VoxelGrid<pcl::PointXYZ> voxelSampler;
        voxelSampler.setInputCloud(cloud.makeShared());
        voxelSampler.setLeafSize(leaf_size, leaf_size, leaf_size);
        voxelSampler.filter(cloud_downsampled);

        pcl::toROSMsg(cloud_downsampled, output);
        pcl_pub.publish(output);

    }
    void reconfigureCB(pcl_test::pcl_test_Config &config,uint32_t level)
    {
    	leaf_size = config.LeafSize;
    	ROS_INFO("%f",leaf_size);
    }
    
protected:
    ros::NodeHandle nh;
    ros::Subscriber pcl_sub;
    ros::Publisher pcl_pub;
    double leaf_size;
    dynamic_reconfigure::Server<pcl_test::pcl_test_Config> server; 
     dynamic_reconfigure::Server<pcl_test::pcl_test_Config>::CallbackType f;
     
    
};

main(int argc, char **argv)
{
    ros::init(argc, argv, "pcl_downsampling");

    cloudHandler handler;

    ros::spin();

    return 0;
}

