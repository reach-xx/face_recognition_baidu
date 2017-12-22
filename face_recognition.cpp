#include "face.h"
#include "FaceIdentify.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using boost::shared_ptr;

// 设置APPID/AK/SK
std::string app_id = "10553810";
std::string api_key = "tETGGBdIdn4zLu4IT34DEX0h";
std::string secret_key = "VIXBrCpBmh6d2H3oZbQF4yPxpD0v7Zb9";

aip::Face client(app_id, api_key, secret_key);

/*添加用户至人脸库中*/
int add_face_database(std::string         uid, std::string user_info, 
			std::string  group_id, const char *imagename)
{
	int ret = 0;
	Json::Value result;
	std::string image;
	ret = aip::get_file_content(imagename, &image);	
	if (ret < 0)
		return -1;
	// 如果有可选参数
	std::map<std::string, std::string> options;
	options["action_type"] = "replace";
	
	// 带参数调用人脸注册
	result = client.user_add(uid,user_info,group_id,image, options);
	return 0;
}


/*从人脸库中删除某用户*/
int del_face_database(std::string uid, std::string group_id)
{
	Json::Value result;

	// 调用人脸删除
	result = client.user_delete(uid, group_id, aip::null);
	return 0;
}


/*从人脸库中更新某用户*/
int update_face_database(std::string uid, std::string group_id, 
									std::string user_info,const char *imagename)
{
	Json::Value result;	
	std::string image;
	int ret ;
	
	ret = aip::get_file_content(imagename, &image);
	if (ret < 0)
		return -1;	

	// 如果有可选参数
	std::map<std::string, std::string> options;
	options["action_type"] = "replace";
	
	// 带参数调用人脸更新
	result = client.user_update(uid, image, user_info, group_id, options);
	return 0;
}


/*从人脸库中查询用户信息*/
int find_user_info(std::string       uid)
{
	return 0;
}


/*查找组下的用户数*/
std::string find_group_users(std::string group_id)
{
	Json::Value result;
	int result_num = 0 , i;
	// 调用组内用户列表查询
	result = client.group_getusers(group_id, aip::null);
	result_num = result["result_num"].asInt();
	printf("Group Users Num: %d\n", result_num);
	Json::Value Items = result["result"];	
	std::cout << "=================find start========================="<< std::endl;
	for (i = 0; i < result_num; i++) 
	{
		Json::Value uid = Items[i]["uid"];	
		Json::Value user_info = Items[i]["user_info"];
		std::cout << uid << user_info << std::endl;
	}
	std::cout << "=================find end========================="<< std::endl;
	std::string ret = result.toStyledString();
	return ret;
}


/*从人脸库中识别*/
std::string face_database_identify(std::string group_id, const char *imageName)
{
	Json::Value result;
	std::string image;

	// 如果有可选参数
	std::map<std::string, std::string> options;
	options["ext_fields"] = "faceliveness";
	options["user_top_num"] = "3";
	
	if(imageName != NULL) {
		aip::get_file_content(imageName, &image);
		// 调用人脸识别
		result = client.identify(group_id, image, aip::null);	
	}
	std::string ret_val = result.toStyledString();
	return ret_val;
}


class FaceIdentifyHandler : virtual public FaceIdentifyIf {
public:
	FaceIdentifyHandler() {
		// Your initialization goes here
	}

	void FI_add_face_database(const std::string& uid, const std::string& user_info, const std::string& group_id, const std::string& imagename) {
		// Your implementation goes here
		const char *pImage = imagename.c_str();
		add_face_database(uid, user_info, group_id, pImage);
		printf("FI_add_face_database\n");
	}

	int32_t FI_del_face_database(const std::string& uid, const std::string& group_id) {
		// Your implementation goes here
		int32_t ret = 0;		
		ret =del_face_database(uid,group_id);
		printf("FI_del_face_database\n");
		return ret;
	}

	int32_t FI_update_face_database(const std::string& uid, const std::string& user_info, const std::string& group_id, const std::string& imagename) {
		// Your implementation goes here
		int32_t ret = 0;		
		const char *pImage = imagename.c_str();		
		update_face_database(uid, user_info, group_id, pImage);
		printf("FI_update_face_database\n");
		return ret;
	}

	int32_t FI_find_user_info(const std::string& uid) {
		// Your implementation goes here
		int32_t ret = 0;
		find_user_info(uid);
		printf("FI_find_user_info\n");
		return ret;
	}

	void FI_find_group_users(std::string& _return, const std::string& group_id) {
		// Your implementation goes here
		_return = find_group_users(group_id);
		std::cout << _return << std::endl;
		printf("FI_find_group_users\n");
	}

	void FI_face_database_identify(std::string& _return, const std::string& group_id, const std::string& imagename) {
		// Your implementation goes here
		const char *pImage = imagename.c_str();
		_return = face_database_identify(group_id,pImage);
		printf("FI_face_database_identify\n");
	}
	
	void FI_face_database_verify(std::string& _return, const std::string& uid, const std::string& user_info, const std::string& group_id, const std::string& imagename) {
		// Your implementation goes here
		std::string temp  = "hello world to China Your implementation goes here!!!\n";
		_return = temp;
		printf("FI_face_database_verify\n");
	}
	
	int32_t FI_group_deleteuser(const std::string& uid, const std::string& group_id) {
		// Your implementation goes here
		int32_t ret = 0;		
		printf("FI_group_deleteuser\n");
		return ret;
	}
	
	int32_t FI_group_adduser(const std::string& src_group_id, const std::string& group_id, const std::string& uid) {
		// Your implementation goes here
		int32_t ret = 0;
		printf("FI_group_adduser\n");
		return ret;
	}

};


int main(int argc, char *argv[])
{
#if 1
	int port = 50040;
	shared_ptr<FaceIdentifyHandler> handler(new FaceIdentifyHandler());
	shared_ptr<TProcessor> processor(new FaceIdentifyProcessor(handler));
	shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	printf("enter Server :\n");
	server.serve();
#endif
#if 0
	int ret = 0;
	std::string uid = "uid008";
	Json::Value result;
	std::string user_info = "张学友";
	std::string group_id = "group1";
	const char *imageName = "zhangxueyou.jpg";
	double score = 0.0;

//	del_face_database(uid,group_id);
//	add_face_database(uid,user_info,group_id,imageName);
	find_group_users(group_id);
	result = face_database_identify(group_id,imageName);
	std::cout << result << std::endl;
#endif	
	return 0;
}



