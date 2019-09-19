/*该例程将请求/spawn服务，服务数据类型为turtlesim::Spawn*/

#include <ros/ros.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv)
{
	//初始化ROS节点
	ros::init(argc, argv, "turtle_spawn");

	//创建节点句柄
	ros::NodeHandle n;

	//发现/spawn服务后，创建一个服务客户端，连接名为/spawn的service
	ros::service::waitForService("/spawn");
	ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("/spawn");

	//初始化turtlesim::Spawn的请求数据
	turtlesim::Spawn srv;
	srv.request.name = "turtle2";
	srv.request.x = 2.0;
	srv.request.y = 2.0;

	//请求服务调用
	ROS_INFO("hu jiao fu wu to spawn turtle[name:%s, x:%0.6f, y:%0.6f]", srv.request.name.c_str(), srv.request.x, srv.request.y);
	
	add_turtle.call(srv);

	//显示服务调用结果
	ROS_INFO("spawn turtle cheng gong! [name:%s]", srv.response.name.c_str());

	return 0;
};
