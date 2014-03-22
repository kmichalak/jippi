/*
 * Copyright 2013 Kamil Michalak <kmichalak8@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */
#include <string.h>     // memcpy
#include <curl/curl.h>    

#include "stringutils/stringutils.hpp"
#include "restclient/restclient.hpp"

using namespace jippi;


RestClient::RestClient()
{
    this->response = new rest_response;
    this->upload_data = new upload_object;
}


RestClient::~RestClient()
{
    delete this->upload_data;
    delete this->response;
}


void RestClient::setAuthorizationData(const std::string& user, const std::string& password)
{
    this->auth_data.clear();
    this->auth_data = user + ":" + password;
}


rest_response RestClient::doHttpGet(const std::string& url)
{
    CURL *curl;
     curl = curl_easy_init();
    setupBuffers();
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERPWD, this->auth_data.c_str());
        
        curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, RestClient::writeCallbackWrapper);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, RestClient::headerCallbackWrapper);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);    

        performRequest(curl);
    }

    curl_easy_cleanup(curl);
    
    return *(this->response);
}


rest_response RestClient::doHttpPut(const std::string& url, const std::string& content_type, const std::string& data)
{
    std::string content_type_header = "Content-Type: " + content_type;
    
     setupBuffers();
    this->upload_data->data = data.c_str();
    this->upload_data->length = data.size();
    
    CURL *curl;
    curl = curl_easy_init();
        
    if (curl) {
        // basic authentication
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERPWD, this->auth_data.c_str());
        
        curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        // set request type to HTTP PUT
        curl_easy_setopt(curl, CURLOPT_PUT, 1L);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        
        // read callback
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, RestClient::readCallbackWrapper);
        curl_easy_setopt(curl, CURLOPT_READDATA, this);
        // write callback 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, RestClient::writeCallbackWrapper);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
        // header callback 
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, RestClient::headerCallbackWrapper);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);    
        
        curl_easy_setopt(curl, CURLOPT_INFILESIZE, static_cast<long>(this->getUploadData()->length));
        
        
        curl_slist* header = curl_slist_append(NULL, content_type_header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
        
        performRequest(curl);
    }
    
    curl_easy_cleanup(curl);
    
    return *(this->response);
}


rest_response RestClient::doHttpPost(const std::string& url, const std::string& content_type, const std::string& data)
{
    std::string content_type_header = "Content-Type: " + content_type;
    
    CURL *curl;
    
    setupBuffers();
    this->upload_data->data = data.c_str();
    this->upload_data->length = data.size();
    
    curl = curl_easy_init();
    curl_slist* header = curl_slist_append(NULL, content_type_header.c_str());
    if (curl) {
        // basic authentication
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERPWD, this->auth_data.c_str());
        
        curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        // set request type to HTTP POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
        
        // write callback 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, RestClient::writeCallbackWrapper);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
        
        // header callback 
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, RestClient::headerCallbackWrapper);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
        
        performRequest(curl);
    }
    
    curl_easy_cleanup(curl);
    header = NULL;
    
    return *(this->response);
}


rest_response* RestClient::getResponse() 
{
    return this->response;
}


upload_object* RestClient::getUploadData() 
{
    return this->upload_data;
}


size_t RestClient::writeCallback(void* outputdata, size_t block_size, size_t block_count, void* inputdata)
{
    size_t output_size = block_size * block_count;
     rest_response* response = reinterpret_cast<rest_response*>(inputdata);
    response->body.append(reinterpret_cast<char*>(outputdata), output_size);
    return output_size;
}


size_t RestClient::readCallback(void* outputdata, size_t block_size, size_t block_count, void* input_data)
{
    upload_object* upload_data = reinterpret_cast<upload_object *>(input_data);
    size_t output_size = block_size * block_count;
    size_t copy_size = (upload_data->length < output_size) ? upload_data->length : output_size;
    
    memcpy(outputdata, upload_data->data, copy_size);
    
    upload_data->length -= copy_size;
    upload_data->data += copy_size;
    
    return copy_size;
}


size_t RestClient::headerCallback(void* output_data, size_t block_size, size_t block_count, void* inputd_ata)
{
    size_t output_size = block_size * block_count;
    rest_response* response = reinterpret_cast<rest_response*>(inputd_ata);
    std::string header_content(reinterpret_cast<char*>(output_data), output_size);
    size_t separator_pos = header_content.find_first_of(":");
    
    if (std::string::npos == separator_pos) {
         header_content = StringUtils::trim(header_content);
        if (StringUtils::isEmpty(header_content)) {
            return output_size;
        }
        response->header[header_content] = "present";
    } else {
        std::string key = StringUtils::trim(header_content.substr(0, separator_pos));
        std::string value = StringUtils::trim(header_content.substr(separator_pos + 1));
        response->header[key] = value;
    }
    
    return output_size;
}


rest_response RestClient::performRequest(CURL *curl)
{
    long http_code = -1;
    CURLcode curl_response = curl_easy_perform(curl);
    
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (curl_response == CURLE_OK) {
        this->response->code = http_code;
    } else {
        this->response->code = curl_response;
        this->response->body = codeToErrorMsg(curl_response);
    }
    
    return *this->response;
}


std::string RestClient::codeToErrorMsg(CURLcode code)
{
    const char *error_msg = curl_easy_strerror(code);
    return std::string(error_msg);
}


size_t RestClient::writeCallbackWrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client)
{
    RestClient* client = static_cast<RestClient*>(rest_client);
    return client->writeCallback(outputdata, block_size, block_count, client->getResponse());
}
    

size_t RestClient::readCallbackWrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client)
{
    RestClient* client = static_cast<RestClient*>(rest_client);
    return client->readCallback(outputdata, block_size, block_count, client->getUploadData());
}
    

size_t RestClient::headerCallbackWrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client)
{
    RestClient* client = static_cast<RestClient*>(rest_client);
    return client->headerCallback(outputdata, block_size, block_count, client->getResponse());
}


bool RestClient::isClean()  
{
    return ( 
        this->response->body.length() == 0 &&
        this->response->code == 0 &&
        this->response->header.size() == 0 &&
        
        this->upload_data->data == NULL &&
        this->upload_data->length == 0
    );
}


void RestClient::flush()
{
    delete this->response;
    delete this->upload_data;
    this->response = new rest_response;
    this->upload_data = new upload_object;
}


void RestClient::setupBuffers() 
{
    if (not isClean()) {
        flush();
    }
}
