#include "ros/ros.h"
#include "std_msgs/String.h"
#include "talker_subscriber/Point.h"
#include <visualization_msgs/Marker.h>
#include <tf/transform_broadcaster.h>
#include <math.h>

class PoseBroadcaster{
public:
  PoseBroadcaster()
  {
  }
  void dummy()
  {
    tf::Transform transform;

    // transform.setOrigin( tf::Vector3(msg->x, msg->y, msg->z));
    transform.setOrigin( tf::Vector3(sin(ros::Time::now().toSec()),
				     1,1));
    transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "my_frame", "testFrameDummy"));
  }

private:
  ros::NodeHandle n_;
  tf::TransformBroadcaster br;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  PoseBroadcaster pb;

  while(ros::ok()) {
    pb.dummy();
    ros::spinOnce();
  }
  ros::spin();
}

  
// void chatterCallback(const talker_subscriber::Point::ConstPtr& msg)
// {
//   ROS_INFO("I heard: [%f]", msg->x);
//   tf::TransformBroadcaster br;
//   tf::Transform transform;

//   transform.setOrigin( tf::Vector3(msg->x, msg->y, msg->z));
//   transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
//   br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "my_frame", "carrot1"));

//   // ros::Rate r(1);
//   // r.sleep();

// }


// int main(int argc, char **argv)
// {


//   ros::init(argc, argv, "listener");

//   ros::NodeHandle n;

//   ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

//   ros::spin();

//   // ros::Rate r(10);
//   // tf::TransformBroadcaster br;
//   // tf::Transform transform;

//   // while (ros::ok()) {
//     // transform.setOrigin( tf::Vector3(1,1,1));
//     // transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
//     // br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "my_frame", "carrot1"));
//   //   r.sleep();
//   // }
  
  

//   return 0;
// }

