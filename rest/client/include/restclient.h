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

typedef struct 
{
	int code;
	std::string body;
} rest_response;


class RestClient
{
public:
	RestClient();
	~RestClient();

	rest_response get(const std::string& url);
	rest_response* create_empty_response();
private:
	static size_t write_callback_wrapper(void* outputdata, size_t block_size, size_t block_count, void* inputdata);
	size_t write_callback(void* outputdata, size_t block_size, size_t block_count, void* inputdata);
	
};

#endif // RESTCLIENT_H

