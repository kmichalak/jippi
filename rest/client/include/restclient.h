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
#include <regex>
#include <map>

typedef std::map<std::string, std::string> response_header;

typedef struct 
{
	int code;
	std::string body;
	response_header header;
} rest_response;


class RestClient
{
public:
	RestClient();
	~RestClient();

	rest_response get(const std::string& url);
	rest_response* create_empty_response();
private:
	static size_t write_callback_wrapper(void* outputdata, size_t block_size, size_t block_count, void* rest_client);
	size_t write_callback(void* outputdata, size_t block_size, size_t block_count, void* inputdata);
	static size_t header_callback_wrapper(void* outputdata, size_t block_size, size_t block_count, void* inputdata);
	size_t header_callback(void* outputdata, size_t block_size, size_t block_count, void* rest_client);
	
	// Trim helpers
// 	std::string trim( std::string && str )
// 	{
// 		size_t end = str.find_last_not_of( " \n\r\t" );
// 		if ( end != std::string::npos ) {
// 			str.resize( end + 1 );
// 		}
// 		size_t start = str.find_first_not_of( " \n\r\t" );
// 		if ( start != std::string::npos ) {
// 			str = str.substr( start );
// 		}
// 		return std::move( str );
// 	}
};

#endif // RESTCLIENT_H

