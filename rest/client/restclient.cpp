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

RestClient::restclient()
{

}

RestClient::~restclient()
{

}

rest_response RestClient::get(const std::string& url)
{
	CURL *curl;
	CURLcode curl_response;

	rest_response* response = new rest_response;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);	// have to add some write callback
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);	// have to add some header callback
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, response);	

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
		
	return response;
}

