/*该例程将请求/show_person服务，服务数据类型为service_test::Person*/

#include <ros/ros.h>
#include <service_test/Person.h>

int main(int argc, char **argv)
{
	//初始化ROS节点
	ros::init(argc, argv, "person_client");

	//创建节点句柄
	ros::NodeHandle n;

	//发现/spawn服务后，创建一个服务客户端，连接名为/show_person的service
	ros::service::waitForService("/show_person");
	ros::ServiceClient person_client = n.serviceClient<service_test::Person>("/show_person");

	//初始化turtlesim::Spawn的请求数据
	service_test::Person srv;
	srv.request.name = "tutu";
	srv.request.age = 23;
	srv.request.sex = service_test::Person::Request::male;

	//请求服务调用
	ROS_INFO("hu jiao fu wu to show person[name:%s, age:%d, sex:%d]", srv.request.name.c_str(), srv.request.age, srv.request.sex);
	
	person_client.call(srv);

	//显示服务调用结果
	ROS_INFO("xian shi person result : %s", srv.response.result.c_str());

	return 0;
};
