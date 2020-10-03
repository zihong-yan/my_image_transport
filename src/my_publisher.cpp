#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("mvcam/image", 1);

  cv::Mat image = cv::imread("/home/yzh/catkin_ws/src/VLC/mvcam/03.BMP", CV_LOAD_IMAGE_COLOR);

  if(image.empty())
  {
      std::cout << "图像加载失败！"<< std::endl;
  }
  
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

  ros::Rate loop_rate(120);
  while (nh.ok()) {
    pub.publish(msg);
    ROS_INFO("good");
    std::cout<<"yzh"<<std::endl;
    ros::spinOnce();
    loop_rate.sleep();
  }
}
