#define _USE_MATH_DEFINES

#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

class PoseListener
{
public:
  void callback(const turtlesim::Pose& msg);
  float x_pos;
  float y_pos;
  float hdg;
};

void PoseListener::callback(const turtlesim::Pose& msg)
{
  PoseListener::x_pos = msg.x;
  PoseListener::y_pos = msg.y;
  PoseListener::hdg = msg.theta;
}


int main(int argc, char **argv) {
   ros::init(argc,argv,"move_to_point");
   ros::NodeHandle nh;

PoseListener listener1;
  ros::Subscriber sub_own = nh.subscribe("turtle1/pose", 1000, &PoseListener::callback, &listener1);  
//PoseListener listener2;
//ros::Subscriber sub_pursuee = nh.subscribe("turtle2/pose", 1000, &PoseListener::callback, &listener2);

  ros::Publisher pub1 = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1000);
  //ros::Publisher pub2 = nh.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",1000);


  while(ros::ok()){
   ros::spinOnce();
float x_target = 10.0;
float y_target = 10.0;
float max_speed = 1.5;
   float rho = sqrt((x_target - listener1.x_pos)*(x_target - listener1.x_pos) 
            + (y_target - listener1.y_pos)*(y_target - listener1.y_pos));
 float brg_angle = atan2(y_target - listener1.y_pos,x_target - listener1.x_pos);
 float kappa = listener1.hdg;   
//float theta = brg_angle + M_PI - listener2.hdg;
        ROS_INFO_STREAM(std::setprecision(2) << std::fixed  << "rho = " << rho);


//Create and fill in the message. The other four fields, which are ignored by turtlesim, default to 0
        geometry_msgs::Twist msg1; //Declare a message of type Twist from the geometry_msgs package

if(0.1*rho>1.5)
{
msg1.linear.x = 1.5;
}
else
{     
msg1.linear.x = 0.1*rho;
}

	float alpha1 = .65*M_PI;
if(sin(brg_angle-kappa) > 0)
{
        msg1.angular.z = .3;
}
else if (sin(brg_angle-kappa) < 0)
{
        msg1.angular.z = -.3;
}
else
{
       msg1.angular.z=0;
}
       // geometry_msgs::Twist msg2; //Declare a message of type Twist from the geometry_msgs package
       // msg2.linear.x = .3;
	//float alpha2 = .65*M_PI;
        //msg2.angular.z = sin(theta-alpha2) + (sin(kappa)+sin(theta))/rho;


        //Publish the message
        pub1.publish(msg1);
        //pub2.publish(msg2);

        //Send a message to rosout with the details
        ROS_INFO_STREAM("Sending velocity command:" << "linear=" <<msg1.linear.x << "angular=" <<msg1.angular.z);

   }   
}
