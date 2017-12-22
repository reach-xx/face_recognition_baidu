#include <iostream>
#include <thrift/transport/TSocket.h>  
#include <thrift/transport/TBufferTransports.h>  
#include <thrift/protocol/TBinaryProtocol.h>  
#include "FaceIdentify.h"  
#include "json/json.h"

using namespace apache::thrift;  
using namespace apache::thrift::protocol;  
using namespace apache::thrift::transport;  
  
using boost::shared_ptr;  
  
int main(int argc, char **argv) {  
	boost::shared_ptr<TSocket> socket(new TSocket("192.168.4.188", 50040));  
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));  
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));  

	transport->open(); 
	//再定义一个对象client
	FaceIdentifyClient client(protocol);
	std::string uid = "uid008";
	std::string user_info = "张学友";
	std::string group_id = "group1";
	std::string imageName = "zhangxueyou.jpg";
	std::string result;
	client.FI_find_group_users(result, group_id);
//	client.FI_face_database_verify(result,uid,user_info,group_id,imageName);
	std::cout << result << std::endl;
	Json::Value root;
	Json::Reader reader;
	if (reader.parse(result, root)) {
		int result_num = root["result_num"].asInt();
		int i;
		Json::Value Items = root["result"];
		printf("==============================================\n");
		for(i = 0; i< result_num ; i++) {
			Json::Value uid = Items[i]["uid"];	
			Json::Value user_info = Items[i]["user_info"];
			std::cout << uid << user_info << std::endl;			
		}
		printf("result_num = %d \n", result_num);
		printf("==============================================\n");		
	}
	
	transport->close();  
	     
	return 0;  
}  
    
