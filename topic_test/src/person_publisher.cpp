/*该例程将发布/person_information话题，自定义消息类型topic_test::Person*/

#include <ros/ros.h>
#include <topic_test/Person.h>

int main(int argc, char **argv)
{
	//ROS节点初始化
	ros::init(argc, argv, "person_publisher");

	//创建节点句柄
	ros::NodeHandle n;

	//创建一个publisher，发布名为/person_information的topic，消息类型为topic_test::Person，队列长度为10
	ros::Publisher person_information_pub = n.advertise<topic_test::Person>("/person_information", 10);

	//设置循环的频率
	ros::Rate loop_rate(1);

	int count = 0;
	while (ros::ok())
	{
		//初始化topic_test::Person类型的消息
		topic_test::Person person_msg;
		person_msg.name = "tutu";
		person_msg.age = 23;
		person_msg.sex = topic_test::Person::male;

		//发布消息
		person_information_pub.publish(person_msg);
		ROS_INFO("publish Person information: name:%s age:%d sex:%d",person_msg.name.c_str(), person_msg.age, person_msg.sex);

		//按照循环频率延时
		loop_rate.sleep();
	}

	return 0;
}
