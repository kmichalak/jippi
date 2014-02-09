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

#ifndef RESTCLIENT_HPP
#define RESTCLIENT_HPP

#include <string>
#include <map>
#include <curl/curl.h>

namespace jippi {

/** Reponse header container */
typedef std::map<std::string, std::string> response_header;


typedef struct 
{
	int code;					/* HTTP response code */
	std::string body;			/* Response body content*/
	response_header header;		/* Response header content*/
} rest_response;


typedef struct
{
	const char* data;
	size_t length;	
} upload_object;


const std::string USER_AGENT = "JIPPI v0.1";

/**
 * REST client definition. 
 */
class RestClient
{
public:
	RestClient();
	~RestClient();

	void setAuthorizationData(const std::string& user, const std::string& password);
	
	rest_response doHttpGet(const std::string& url);
	rest_response doHttpPut(const std::string& url, const std::string& content_type, const std::string& data);
	rest_response doHttpPost(const std::string& url, const std::string& content_type, const std::string& data);
	rest_response* crateEmptyResponse();
	upload_object* getUploadData();
	
private:
	rest_response* response;
	upload_object* upload_data;
	std::string auth_data;
	
	size_t writeCallback(void* outputdata, size_t block_size, size_t block_count, void* input_data);
	size_t readCallback(void* outputdata, size_t block_size, size_t block_count, void* input_data);
	size_t headerCallback(void* outputdata, size_t block_size, size_t block_count, void* input_data);
	rest_response performRequest(CURL *curl);
	std::string codeToErrorMsg(CURLcode code);
	
	/**
	 * The solution suggested by CURL documentation available at 
	 * http://curl.haxx.se/docs/faq.html#Using_C_non_static_functions_f
	 * I know this is ugly, but I hate static methods... If it has to be static
	 * let it do the least as it's possible.
	 */
	static size_t writeCallbackWrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client)
	{
		RestClient* client = static_cast<RestClient*>(rest_client);
		return client->writeCallback(outputdata, block_size, block_count, client->crateEmptyResponse());
	}
	
	/**
	 * The solution suggested by CURL documentation available at 
	 * http://curl.haxx.se/docs/faq.html#Using_C_non_static_functions_f
	 * I know this is ugly, but I hate static methods... If it has to be static
	 * let it do the least as it's possible.
	 */	
	static size_t readCallbackWrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client)
	{
		RestClient* client = static_cast<RestClient*>(rest_client);
		return client->readCallback(outputdata, block_size, block_count, client->getUploadData());
	}
	
	/**
	 * The solution suggested by CURL documentation available at 
	 * http://curl.haxx.se/docs/faq.html#Using_C_non_static_functions_f
	 * I know this is ugly, but I hate static methods... If it has to be static
	 * let it do the least as it's possible.
	 */
	static size_t headerCallbackWrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client)
	{
		RestClient* client = static_cast<RestClient*>(rest_client);
		return client->headerCallback(outputdata, block_size, block_count, client->crateEmptyResponse());
	}
	
	
};

} // end of namespace

#endif // RESTCLIENT_H

