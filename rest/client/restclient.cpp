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

#include "include/restclient.h"
#include <curl/curl.h>
#include <tr1/functional>

const char* USER_AGENT = "JIPPI v0.1";

RestClient::RestClient()
{

}

RestClient::~RestClient()
{

}

/**
 * @brief HTTP GET method.
 * 
 * @param url - the URL to query
 * @return response from REST server
 */
rest_response RestClient::get(const std::string& url)
{
	CURL *curl;
	CURLcode curl_response;

	rest_response* response = new rest_response;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_wrapper);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);	// have to add some header callback
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);	

		curl_response = curl_easy_perform(curl);

		if (curl_response == CURLE_OK) {
			long http_code = 0;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
			response->code = http_code;
			
		} else {
			response->body = "FAIL";
			response->code = -1;    // have to introduce some constant for query failure
		}
	}

	curl_easy_cleanup(curl);
	
	return *response;
}

/**
 * The solution suggested by CURL documentation available at 
 * http://curl.haxx.se/docs/faq.html#Using_C_non_static_functions_f
 * I know this is ugly, but I hate static methods... If it has to be static
 * let it do the least as it's possible.
 */
size_t RestClient::write_callback_wrapper(void* outputdata, 
					  size_t block_size, 
					  size_t block_count, 
					  void* rest_client)
{
	RestClient* client = static_cast<RestClient*>(rest_client);
	return client->write_callback(outputdata, block_size, block_count, client->create_empty_response());
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

rest_response* RestClient::create_empty_response() 
{
	return new rest_response;
}
