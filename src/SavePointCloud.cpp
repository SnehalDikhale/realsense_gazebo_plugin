/*
Used to save the point cloud data in an OBJ file 
Application: Would be used while training Dex-net 
Disclaimer: Not used for Comparison of the Grasping Algorithms
Reason for not using: Used Pre-trained model for the project
*/

#include <iostream> 
#include <stdio.h> 
#include <fstream>
#include <time.h>

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

// PCL specific includes
#include <pcl_ros/point_cloud.h>

using namespace cv;
int write_flag = 0;

void cloud_cb (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& msg){
  if (::write_flag == 1){
    ::write_flag = 0;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char name [50];
    sprintf(name, "%04d_%02d_%02d_%02d%02d%02d.obj", 1900 + ltm->tm_year,1 + ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec);
    std::string OpName = name;
    std::ofstream os(OpName.c_str());
    const size_t size = msg->points.size();
    for(unsigned int i=0 ; i<size ; i++){
        // Remove nan
        if(!std::isnan(msg->points[i].x))
        {
            os << "v ";
            os << msg->points[i].x << " ";
            os << msg->points[i].y << " ";
            os << msg->points[i].z << "\n";
        }
    }

    os.close();
    std::cout << name << std::endl;
    
  }
}

void rgb_cb(const sensor_msgs::Image::ConstPtr& msg){

    try {
        cv_bridge::CvImageConstPtr cv_ptr;
        cv_ptr = cv_bridge::toCvShare(msg);
	

        imshow("RGB Stream", cv_ptr->image);
        int k = waitKey(1);  // Update screen
        // Press "P" to save point cloud
        if (k == 112 ){
          std::cout << "Saving Point Cloud" << std::endl;
          ::write_flag = 1;
        }
        // Press "Esc" to exit
        else if (k == 27){
          ros::shutdown();
        }
    } 
        catch (const cv_bridge::Exception& e){
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}

int main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "Save_PointCloud");
  ros::NodeHandle nh;

  std::cout << "\nStarting the subscribers" << std::endl;
  std::cout << "Press \"P\" to save Point cloud and \"Esc\" to exit"  << std::endl;

  // Create a ROS subscriber for the rgb & point cloud
  ros::Subscriber sub_rgb = nh.subscribe ("/r200/camera/color/image_raw", 1, rgb_cb);
  ros::Subscriber sub_pc = nh.subscribe ("/r200/camera/depth_registered/points", 1, cloud_cb);
  
  namedWindow("RGB Stream");
  ros::spin ();
  destroyWindow("RGB Stream");
  std::cout << "Code Terminated\n" << std::endl;

  return 0;
}

