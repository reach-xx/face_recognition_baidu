#include "face.h"

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
int find_user_info(char *uid)
{
	return 0;
}


/*查找组下的用户数*/
int find_group_users(std::string group_id)
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
	return 0;
}


/*从人脸库中识别*/
Json::Value face_database_identify(std::string group_id, const char *imageName)
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
	return result;
}


int main(int argc, char *argv[])
{
	int ret = 0;
	std::string uid = "uid008";
	Json::Value result;
	std::string user_info = "张学友";
	std::string group_id = "group1";
	const char *imageName = "zhangxueyou.jpg";
	double score = 0.0;

//	del_face_database(uid,group_id);
	add_face_database(uid,user_info,group_id,imageName);
	find_group_users(group_id);
	result = face_database_identify(group_id,imageName);
//	std::cout << result << std::endl;
	Json::Value res = result["result"];
	const char *info = res[0]["user_info"].asCString();
	score = res[0]["scores"][0].asDouble();
	printf("name:%s        Scores:%f\n",info,score);
	
	return 0;
}



