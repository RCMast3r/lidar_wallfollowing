#include "lidar_wallfollowing.hpp"
int main(int argc, char **argv){

    ros::init(argc, argv, "test");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");
    lidar_wallfollowing::lidar_wallfollowing inst(nh, pnh);
    
    ros::spin();
    return 0;
}
