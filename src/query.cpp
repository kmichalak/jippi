/*
 * Copyright 2014 Kamil Michalak <kmichalak8@gmail.com>
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

#include <iostream>
#include <assert.h>

#include "inc/query.hpp"
#include "inc/restclient.hpp"
#include "inc/stringutils.hpp"


using namespace jippi;

Query::Query(std::string queryURL)
{
	assert(!jippi::StringUtils::isEmpty(queryURL) && "Target URL cannot be empty!");
	this->queryURL = queryURL;
	restClient = new RestClient();
	jsonWriter = new Json::StyledWriter();
}

Query::~Query()
{
	delete jsonWriter;
	delete restClient;
}

void Query::withProject(std::string project)
{
	queryParams["jql"] = "project="+project;
}

void Query::withAssignee(std::string assignee)
{
	queryParams["assignee"] = assignee;
}

void Query::execute()
{
	std::string jsonString = jsonWriter->write(queryParams);
	std::cout << "Passing JSON: " + jsonString << std::endl;
	rest_response response = restClient->doHttpPost(
		queryURL, "application/json", jsonString
	);
	std::cout << response.body << std::endl;
	std::cout << jsonString << std::endl;
}

std::string Query::getJsonPayload()
{
	std::string payload = jsonWriter->write(queryParams);
	return payload;
}

