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

#include "../inc/restclient.hpp"
#include "../inc/stringutils.hpp"
#include <curl/curl.h>
#include <tr1/functional>
#include <stdio.h>
#include <cstring>

RestClient::RestClient()
{

}


RestClient::~RestClient()
{

}


/**
 * @brief Setups authorization data for REST request.
 * 
 * @param user - user name
 * @param password - user password
 */
void RestClient::set_authorization_data(const std::string& user, const std::string& password)
{
	this->auth_data.clear();
	this->auth_data = user + ":" + password;
}


/**
 * @brief HTTP GET method.
 * 
 * @param url - the URL to query
 * @return response from REST server
 */
rest_response RestClient::get(const std::string& url)
{
	const char* USER_AGENT = "JIPPI v0.1";
	
	CURL *curl;
	CURLcode curl_response;

 	this->response = new rest_response;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_easy_setopt(curl, CURLOPT_USERPWD, this->auth_data.c_str());
		
		curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, RestClient::write_callback_wrapper);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, RestClient::header_callback_wrapper);	// have to add some header callback
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);	

		curl_response = curl_easy_perform(curl);

		if (curl_response == CURLE_OK) {
			long http_code = 0;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
			this->response->code = http_code;
		} else {
			this->response->body = "FAIL";
			this->response->code = -1;    // have to introduce some constant for query failure
		}
	}

	curl_easy_cleanup(curl);
	
	return *(this->response);
}


/**
 * @brief Callback for CURL write function. 
 * As it's mentioned in CURL documentation callback should 
 * use a fwrite() syntax.
 * 
 * @param outputdata - output data of size (\a block_size * \a block_count)
 * @param block_size - size in bytes of each element to be written
 * @param block_count - number of elements, each one with a size of 
 * 			\a block_size_ bytes
 * @param inputdata - pointer to user data to work with when creating 
 * 		      \a outputdata
 */
size_t RestClient::write_callback(void* outputdata, size_t block_size, size_t block_count, void* inputdata)
{
	size_t output_size = block_size * block_count;
 	rest_response* response = reinterpret_cast<rest_response*>(inputdata);
	response->body.append(reinterpret_cast<char*>(outputdata), output_size);
	return output_size;
}


size_t RestClient::header_callback(void* output_data, size_t block_size, size_t block_count, void* inputd_ata)
{
	size_t output_size = block_size * block_count;
	rest_response* response = reinterpret_cast<rest_response*>(inputd_ata);
	std::string header_content(reinterpret_cast<char*>(output_data), output_size);
	size_t separator_pos = header_content.find_first_of(":");
	
	if (std::string::npos == separator_pos) {
 		header_content = StringUtils::trim(header_content);
		if (StringUtils::is_empty(header_content)) {
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


rest_response RestClient::put(const std::string& url, const std::string& content_type, const std::string& data)
{
	const char* USER_AGENT = "JIPPI v0.1";
	
	std::string content_type_header = "Content-Type: " + content_type;
	
	CURL *curl;
	CURLcode curl_response;
	
	this->response = new rest_response;
	this->upload_data = new upload_object;
	this->upload_data->data = data.c_str();
	this->upload_data->length = data.size();
	
	curl = curl_easy_init();
	if (curl) {
		// basic authentication
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_easy_setopt(curl, CURLOPT_USERPWD, this->auth_data.c_str());
		
		curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		
		// set request type to HTTP PUT
		curl_easy_setopt(curl, CURLOPT_PUT, 1L);
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		
		// read callback
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, RestClient::read_callback_wrapper);
		curl_easy_setopt(curl, CURLOPT_READDATA, this);
		// write callback 
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, RestClient::write_callback_wrapper);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		// header callback 
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, RestClient::header_callback_wrapper);	// have to add some header callback
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);	
		
		curl_easy_setopt(curl, CURLOPT_INFILESIZE, static_cast<long>(this->get_upload_data()->length));
		
		
		curl_slist* header = curl_slist_append(NULL, content_type_header.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
		
		curl_response = curl_easy_perform(curl);
		
		if (curl_response == CURLE_OK) {
			long http_code = 0;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
			this->response->code = http_code;
		} else {
			this->response->body = "FAIL";
			this->response->code = -1;    // have to introduce some constant for query failure
		}
	}
	
	curl_easy_cleanup(curl);
	
	return *(this->response);
}


size_t RestClient::read_callback(void* outputdata, size_t block_size, size_t block_count, void* input_data)
{
	upload_object* upload_data = reinterpret_cast<upload_object *>(input_data);
	size_t output_size = block_size * block_count;
	size_t copy_size = (upload_data->length < output_size) ? upload_data->length : output_size;
	
	memcpy(outputdata, upload_data->data, copy_size);
	
	upload_data->length -= copy_size;
	upload_data->data += copy_size;
	
	return copy_size;
}


rest_response* RestClient::create_empty_response() 
{
	return this->response;
}

upload_object* RestClient::get_upload_data() 
{
	return this->upload_data;
}