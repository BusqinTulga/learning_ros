/*该例程将订阅/person_information话题，自定义消息类型topic_test::Person*/

#include <ros/ros.h>
#include <topic_test/Person.h>

//接受到订阅的消息后，会进入消息回调函数
void poseCallback(const topic_test::Person::ConstPtr& msg)
{
	//将接受到的消息打印出来
	ROS_INFO("subscribe Person information: name:%s age:%d sex:%d", msg->name.c_str(), msg->age, msg->sex);
}

int main(int argc,char **argv)
{
	//初始化ROS节点
	ros::init(argc, argv, "person_subscriber");

	//创建节点句柄
	ros::NodeHandle n;

	//创建一个Subscriber，订阅名为/person_information的topic，注册回调函数poseCallback
	ros::Subscriber person_information_sub = n.subscribe("/person_information", 10, poseCallback);

	//循环等待回调函数
	ros::spin();

	return 0;
}
