/*该例程将执行/turtle_command服务，服务数据类型为std_srvs/Trigger*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Trigger.h>

ros::Publisher turtle_vel_pub;
bool pubCommand = false;

//service回调函数，输入参数req，输出参数res
bool commandCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res)
{
	pubCommand = !pubCommand;

	//显示请求数据
	ROS_INFO("fa bu turtle su du kong zhi [%s]", pubCommand == true? "Yes":"No");

	//设置反馈数据
	res.success = true;
	//req.message = "geng gai turtle kong zhi state!";

	return true;
}

int main(int argc, char **argv)
{
	//ROS节点初始化
	ros::init(argc, argv, "turtle_command_server");

	//创建节点句柄
	ros::NodeHandle n;

	//创建一个名为/turtle_command的server，注册回调函数commandCallback
	ros::ServiceServer command_service = n.advertiseService("/turtle_command", commandCallback);

	//创建一个Publisher，发布名为/turtle1/cmd_vel的topic，消息类型为geometry_msgs::Tuist，队列长度为10
	turtle_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

	//循环等待回调函数
	ROS_INFO("yi zhun bei hao jie shou turtle command.");

	//设置循环的频率
	ros::Rate loop_rate(10);

	while(ros::ok())
	{
		//查看一次回调函数队列
		ros::spinOnce();

		//如果标志为true，则发布速度指令
		if(pubCommand)
		{
			geometry_msgs::Twist vel_msg;
			vel_msg.linear.x = 1.0;
			vel_msg.linear.y = 1.0;
			turtle_vel_pub.publish(vel_msg);
		}

		//按照循环频率延时
		loop_rate.sleep();
	}

	return 0;
}
