#include "lidar_wallfollowing.hpp"

namespace lidar_wallfollowing 
{
    lidar_wallfollowing::lidar_wallfollowing(ros::NodeHandle& nh, ros::NodeHandle &pnh) : nh_(nh), pnh_(pnh)
    {
        loadParameters();
        subscribeToTopics();
        publishToTopics();
   }

    void lidar_wallfollowing::loadParameters() {
        
        if (!pnh_.param<std::string>("laser_scan_topic_name", laser_scan_topic_name_, "/scan")) {
        ROS_WARN_STREAM(
            "Did not load laser_scan_topic_name. Standard value is: " << laser_scan_topic_name_);
        }
        if (!pnh_.param<std::string>("command_topic_name", command_topic_name_, "/cmd_vel")) {
        ROS_WARN_STREAM(
            "Did not load command_topic_name. Standard value is: " << command_topic_name_);
        }
        if (!pnh_.param<int>("upper_scan_index", upper_scan_index_, 90)) {
        ROS_WARN_STREAM(
            "Did not load upper_scan_index. Standard value is: " << upper_scan_index_);
        } 
        if (!pnh_.param<float>("min_dist", min_dist_, 0.5)) { // the minimum distance the bot can be from the wall on it's right
        ROS_WARN_STREAM(
            "Did not load min_dist. Standard value is: " << min_dist_);
        }
        if (!pnh_.param<float>("max_dist", max_dist_, 2.0)) { // the max distance the bot can be from the wall on it's right
        ROS_WARN_STREAM(
            "Did not load min_dist. Standard value is: " << max_dist_);
        }

        // if (!pnh_.param<int>("angle_index", laser_scan_topic_name_, 120)) {
        // ROS_WARN_STREAM(
        //     "Did not load laser_scan_topic_name. Standard value is: " << laser_scan_topic_name_);
        // }

    }
    void lidar_wallfollowing::subscribeToTopics()
    {
        laser_subscriber_=nh_.subscribe(laser_scan_topic_name_,1, &lidar_wallfollowing::lidar_wallfollowing::laserCallback,this);
    }
    void lidar_wallfollowing::publishToTopics()
    {
        command_=nh_.advertise<geometry_msgs::Twist>(command_topic_name_,1);
    }
    void lidar_wallfollowing::laserCallback(const sensor_msgs::LaserScan scan){

        float angz_val;
        float linx_val;
       
    //    ROS_INFO_STREAM("minimum range in msg: " << scan.range_min);
    //    ROS_INFO_STREAM("maximmum range in msg: " << scan.range_max);

    //    auto it = std::max_element(std::begin(scan.ranges), std::end(scan.ranges));
    //     ROS_INFO_STREAM("max using max_element: "<<*it);
    
        float min = *min_element(scan.ranges.begin(), scan.ranges.end());
        

        int len = scan.ranges.size();
        float max = 0.0;
        for (int i=0; i < scan.ranges.size(); i++) {
            if( !isinf(scan.ranges.at(i)) && scan.ranges.at(i) >= max){
                max =scan.ranges.at(i);
            }
        }
        bool nothing_on_right = scan.ranges.at(270) > 2.0;
        bool something_in_front = scan.ranges.at(350) < 2.0;
        // ROS_INFO_STREAM("minimum using min element: " << min);
        // ROS_INFO_STREAM("max using regular method: " << max);
        if(nothing_on_right) {
            ROS_INFO_STREAM("there is nothing directly on the right");
        }

        
        
        // if either of the "control distances" read as inf, go forward
        // 
        //   else if the distance (D) to the right (scan at range 0)*cos(alpha) is greater than (config) turn right toward wall (bigly difference in wheel speeds)
        //   else if the distance (D) to the right (scan at range 0) is less than (config) turn left away from the wall (bigly difference in wheel speeds)



        // turning right is negative 1 z / left is positive 1
        // float alpha = atan( ((scan.ranges.at(270+upper_scan_index_)*cos(270+upper_scan_index_)) - scan.ranges.at(270))/(scan.ranges.at(270+upper_scan_index_)*sin(270+upper_scan_index_)) );

        // float D = scan.ranges.at(0) * cos(alpha);


        if( (nothing_on_right && !something_in_front) ){
            linx_val = 0.15;
            angz_val = -0.4; // TURN RIGHT
            ROS_INFO_STREAM("turning right");
        } else if( (something_in_front)  ) {
            linx_val = 0.15;
            angz_val = 0.4; // turn LEFT
            ROS_INFO_STREAM("turning left");
        } else {    
            linx_val = 0.2; // 
            angz_val = 0.0;
        }


        command_msg_.linear.x = linx_val;
        command_msg_.angular.z = angz_val;

        command_.publish(command_msg_);


        



    }



}