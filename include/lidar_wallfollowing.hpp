#include <ros/ros.h>
#include <ackermann_msgs/AckermannDrive.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <cmath>
#include <limits>
#include <algorithm>
namespace lidar_wallfollowing{

class lidar_wallfollowing{
    public:
        lidar_wallfollowing(ros::NodeHandle& nh, ros::NodeHandle& pnh);

    private:
    

    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;

    ros::Publisher ackermann_command_;
    ros::Subscriber laser_subscriber_;
    ackermann_msgs::AckermannDrive command_;

    std::string laser_scan_topic_name_;
    std::string ackermann_command_topic_name_;
    // float theta_;
    // float ACerror_;
    // int upper_index_;
    // int right_index_;
    // float desired_dist_;
    // float kp_;
    // float kd_;
    // float set_vel_;
    // float abs_servo_max_;
    // float servo_speed_;
    
    // float alpha_;
    // float CDdist_;
    // float ABdist_;
    // float prev_CDdist_=0;
    // float servo_pos_;
    void publishToTopics();
    void subscribeToTopics();
    void loadParameters();

    void laserCallback(const sensor_msgs::LaserScan scan);
    
    // void calcAlpha(const sensor_msgs::LaserScan scan);
    template <typename T, size_t N> const T* mybegin(const T (&a)[N]) { return a; }
    template <typename T, size_t N> const T* myend  (const T (&a)[N]) { return a+N; }

    

    
};
}
