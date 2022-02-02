#include "lidar_wallfollowing.hpp"

namespace lidar_wallfollowing 
{
    lidar_wallfollowing::lidar_wallfollowing(ros::NodeHandle& nh, ros::NodeHandle &pnh) : nh_(nh), pnh_(pnh)
    {
        loadParameters();
        subscribeToTopics();
   }

    void lidar_wallfollowing::loadParameters() {
        
        if (!pnh_.param<std::string>("laser_scan_topic_name", laser_scan_topic_name_, "/yeet")) {
        ROS_WARN_STREAM(
            "Did not load laser_scan_topic_name. Standard value is: " << laser_scan_topic_name_);
        }

    }
    void lidar_wallfollowing::subscribeToTopics()
    {
        laser_subscriber_=nh_.subscribe(laser_scan_topic_name_,1, &lidar_wallfollowing::lidar_wallfollowing::laserCallback,this);
    }
    void lidar_wallfollowing::laserCallback(const sensor_msgs::LaserScan scan){
       
       ROS_INFO_STREAM("minimum range in msg: " << scan.range_min);
       ROS_INFO_STREAM("maximmum range in msg: " << scan.range_max);

    //    auto it = std::max_element(std::begin(scan.ranges), std::end(scan.ranges));
    //     ROS_INFO_STREAM("max using max_element: "<<*it);
    
        float min = *min_element(scan.ranges.begin(), scan.ranges.end());

        float max = 0.0;
        for (int i=0; i<scan.ranges.size(); i++) {
            if( !isinf(scan.ranges.at(i)) && scan.ranges.at(i) >= max){
                max =scan.ranges.at(i);
            }
        }
        ROS_INFO_STREAM("minimum using min element: " << min);
        ROS_INFO_STREAM("max using regular method: " << max);


    }



}