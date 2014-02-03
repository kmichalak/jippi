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

#include "inc/getissueaction.hpp"
#include "inc/config.hpp"
#include "inc/restclient.hpp"

#include "inc/jira.hpp"

using namespace jippi;

GetIssueAction::GetIssueAction()
{

}

GetIssueAction::~GetIssueAction()
{
	
}

void GetIssueAction::perform()
{
	const std::string jiraUrl = configuration->getProperty(JIRA_GROUP, JIRA_URL) + SEARCH_URL_SUFFIX ;
	const std::string jiraUser = configuration->getProperty(JIRA_GROUP, JIRA_USER);
	const std::string jiraPassword = configuration->getProperty(JIRA_GROUP, JIRA_PASSWORD);
	
	std::string jsonPayload = getJSONPayload();
	
	restClient->setAuthorizationData(jiraUser, jiraPassword);
	rest_response response = restClient->doHttpPost(jiraUrl, "application/json", jsonPayload);
	std::cout << response.code << " : " << response.body << std::endl;
	
}



	

