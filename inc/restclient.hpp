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

#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <string>
#include <map>

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

/**
 * REST client definition. 
 */
class RestClient
{
public:
	RestClient();
	~RestClient();

	void set_authorization_data(const std::string& user, const std::string& password);
	
	rest_response get(const std::string& url);
	rest_response put(const std::string& url, const std::string& content_type, const std::string& data);
	rest_response* create_empty_response();
	upload_object* get_upload_data();
	
private:
	rest_response* response;
	upload_object* upload_data;
	std::string auth_data;
	
	size_t write_callback(void* outputdata, size_t block_size, size_t block_count, void* input_data);
	size_t header_callback(void* outputdata, size_t block_size, size_t block_count, void* input_data);
	size_t read_callback(void* outputdata, size_t block_size, size_t block_count, void* input_data);
	
	/**
	 * The solution suggested by CURL documentation available at 
	 * http://curl.haxx.se/docs/faq.html#Using_C_non_static_functions_f
	 * I know this is ugly, but I hate static methods... If it has to be static
	 * let it do the least as it's possible.
	 */
	static size_t write_callback_wrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client)
	{
		RestClient* client = static_cast<RestClient*>(rest_client);
		return client->write_callback(outputdata, block_size, block_count, client->create_empty_response());
	}
	
	/**
	 * The same solution as write_callback_wrapper. For more details look at 
	 * http://curl.haxx.se/docs/faq.html#Using_C_non_static_functions_f.
	 */
	static size_t header_callback_wrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client)
	{
		RestClient* client = static_cast<RestClient*>(rest_client);
		return client->header_callback(outputdata, block_size, block_count, client->create_empty_response());
	}
	
	static size_t read_callback_wrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client)
	{
		RestClient* client = static_cast<RestClient*>(rest_client);
		return client->read_callback(outputdata, block_size, block_count, client->get_upload_data());
	}
};

} // end of namespace

#endif // RESTCLIENT_H

