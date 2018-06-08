#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "publish_velocity"); //publish velocity is now the name of our node
	ros::NodeHandle nh;

	//Create a publisher object. 
		//nh is our node handle
		//The message type is in < >
		//We put the topic name in quotes
		//1000 is the number of messages we'll allow to stack up in the queue
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1000);

	//Seed the random number generator
	srand(time(0));

	//Loop at 2Hz until the node is shut down
	ros::Rate rate(2);
	while(ros::ok()) //Check if our node is still in "good standing" as a ROS node
	{
	//Create and fill in the message. The other four fields, which are ignored by turtlesim, default to 0
	geometry_msgs::Twist msg; //Declare a message of type Twist from the geometry_msgs package
	msg.linear.x = double(rand())/double(RAND_MAX);
	msg.angular.z = 2*double(rand())/double(RAND_MAX) - 1;

	//Publish the message
	pub.publish(msg);

	//Send a message to rosout with the details
	ROS_INFO_STREAM("Sending random velocity command:" << "linear=" <<msg.linear.x << "angular=" <<msg.angular.z);

	//Wait until time for another iteration
	rate.sleep(); //The actual delay time will be calculated by ROS to fulfill the rate we specified earlier with the ros::Rate line
	}

}
