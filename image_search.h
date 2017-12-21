/**
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 * @author baidu aip
 */

#ifndef __AIP_IMAGESEARCH_H__
#define __AIP_IMAGESEARCH_H__

#include "base/base.h"

namespace aip {

    class Imagesearch: public AipBase
    {
    public:

    
        std::string _same_hq_add =
            "https://aip.baidubce.com/rest/2.0/realtime_search/same_hq/add";
        
        std::string _same_hq_search =
            "https://aip.baidubce.com/rest/2.0/realtime_search/same_hq/search";
        
        std::string _same_hq_delete =
            "https://aip.baidubce.com/rest/2.0/realtime_search/same_hq/delete";
        
        std::string _similar_add =
            "https://aip.baidubce.com/rest/2.0/image-classify/v1/realtime_search/similar/add";
        
        std::string _similar_search =
            "https://aip.baidubce.com/rest/2.0/image-classify/v1/realtime_search/similar/search";
        
        std::string _similar_delete =
            "https://aip.baidubce.com/rest/2.0/image-classify/v1/realtime_search/similar/delete";
        

        Imagesearch(const std::string & app_id, const std::string & ak, const std::string & sk): AipBase(app_id, ak, sk)
        {
        }
        
        /**
         * same_hq_add
         * 该请求用于实时检索相同图片集合。即对于输入的一张图片（可正常解码，且长宽比适宜），返回自建图库中相同的图片集合。相同图检索包含入库、检索、删除三个子接口；**在正式使用之前请加入QQ群：649285136 联系工作人员完成建库并调用入库接口完成图片入库**。
         * @param image 图像文件二进制内容，可以使用aip::get_file_content函数获取
         * options 可选参数:
         * brief 检索时原样带回,最长256B。
         */
        Json::Value same_hq_add(
            std::string const & image,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["image"] = base64_encode(image.c_str(), (int) image.size());

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_same_hq_add, null, data, null);

            return result;
        }
        
        /**
         * same_hq_search
         * 使用该接口前，请加入QQ群：649285136 ，联系工作人员完成建库。
         * @param image 图像文件二进制内容，可以使用aip::get_file_content函数获取
         * options 可选参数:
         */
        Json::Value same_hq_search(
            std::string const & image,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["image"] = base64_encode(image.c_str(), (int) image.size());

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_same_hq_search, null, data, null);

            return result;
        }
        
        /**
         * same_hq_delete_by_image
         * 删除相同图
         * @param image 图像文件二进制内容，可以使用aip::get_file_content函数获取
         * options 可选参数:
         */
        Json::Value same_hq_delete_by_image(
            std::string const & image,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["image"] = base64_encode(image.c_str(), (int) image.size());

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_same_hq_delete, null, data, null);

            return result;
        }
        
        /**
         * same_hq_delete_by_sign
         * 删除相同图
         * @param cont_sign 图片签名（和image二选一，image优先级更高）
         * options 可选参数:
         */
        Json::Value same_hq_delete_by_sign(
            std::string const & cont_sign,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["cont_sign"] = cont_sign;

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_same_hq_delete, null, data, null);

            return result;
        }
        
        /**
         * similar_add
         * 该请求用于实时检索相似图片集合。即对于输入的一张图片（可正常解码，且长宽比适宜），返回自建图库中相似的图片集合。相似图检索包含入库、检索、删除三个子接口；**在正式使用之前请加入QQ群：649285136 联系工作人员完成建库并调用入库接口完成图片入库**。
         * @param image 图像文件二进制内容，可以使用aip::get_file_content函数获取
         * options 可选参数:
         * brief 检索时原样带回,最长256B。
         */
        Json::Value similar_add(
            std::string const & image,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["image"] = base64_encode(image.c_str(), (int) image.size());

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_similar_add, null, data, null);

            return result;
        }
        
        /**
         * similar_search
         * 使用该接口前，请加入QQ群：649285136 ，联系工作人员完成建库。
         * @param image 图像文件二进制内容，可以使用aip::get_file_content函数获取
         * options 可选参数:
         */
        Json::Value similar_search(
            std::string const & image,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["image"] = base64_encode(image.c_str(), (int) image.size());

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_similar_search, null, data, null);

            return result;
        }
        
        /**
         * similar_delete_by_image
         * 删除相似图
         * @param image 图像文件二进制内容，可以使用aip::get_file_content函数获取
         * options 可选参数:
         */
        Json::Value similar_delete_by_image(
            std::string const & image,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["image"] = base64_encode(image.c_str(), (int) image.size());

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_similar_delete, null, data, null);

            return result;
        }
        
        /**
         * similar_delete_by_sign
         * 删除相似图
         * @param cont_sign 图片签名（和image二选一，image优先级更高）
         * options 可选参数:
         */
        Json::Value similar_delete_by_sign(
            std::string const & cont_sign,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["cont_sign"] = cont_sign;

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_similar_delete, null, data, null);

            return result;
        }
        

    };
}
#endif