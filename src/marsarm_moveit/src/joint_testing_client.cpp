#include "ros/ros.h"
#include "marsarm_moveit/Joints.h"

int main(int argc, char **argv){
  ros::init(argc, argv, "joint_angle_publisher");
  // if (argc != 7){
  //   ROS_INFO("usage: currently, adds the norm of two vectors x y z x y z");
  //   return 1;
  // }

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<marsarm_moveit::Joints>("/actual_joints", 10);





  marsarm_moveit::Joints j;
  j.joints.resize(7);
  j.joints[0] = atof(argv[1]);
  j.joints[1] = atof(argv[2]);
  j.joints[2] = atof(argv[3]);
  j.joints[3] = atof(argv[4]);
  j.joints[4] = atof(argv[5]);
  j.joints[5] = atof(argv[6]);
  j.joints[6] = atof(argv[7]);
  // srv.request.start.x = atof(argv[1]);

  sleep(2);
  pub.publish(j);
  sleep(1);

  
  return 0;
}
  












