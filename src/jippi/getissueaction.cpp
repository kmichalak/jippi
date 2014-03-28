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

#include <include/jippi/jippi.hpp>
#include "jippi/getissueaction.hpp"

#include "jippi/jira.hpp"
#include "jippi/jsonparser.hpp"

using namespace jippi;

GetIssueAction::GetIssueAction()
{

}

GetIssueAction::~GetIssueAction()
{
    
}

void GetIssueAction::perform() {
    const std::string jiraUrl =
            configuration->getProperty(JIRA_GROUP, JIRA_URL) + SEARCH_URL_SUFFIX;
    const std::string jiraUser = configuration->getProperty(JIRA_GROUP, JIRA_USER);
    const std::string jiraPassword = configuration->getProperty(JIRA_GROUP, JIRA_PASSWORD);

    if (StringUtils::isEmpty(jiraUrl)) {
        throw EmptyConfigurationValueException(JIRA_GROUP, JIRA_URL);
    }

    if (StringUtils::isEmpty(jiraUser)) {
        throw EmptyConfigurationValueException(JIRA_GROUP, JIRA_USER);
    }

    if (StringUtils::isEmpty(jiraPassword)) {
        throw EmptyConfigurationValueException(JIRA_GROUP, JIRA_PASSWORD);
    }

    std::string jsonPayload = getJSONPayload();
    if (jsonPayload.empty()) {
        throw InvalidQueryException("At least one query parameter must be specified.");
    }

    if (isInDebugMode) {
        std::cout << std::endl << jsonPayload << std::endl;
    }

    restClient->setAuthorizationData(jiraUser, jiraPassword);
    rest_response response = restClient->doHttpPost(jiraUrl, "application/json", jsonPayload);

    JsonParser *jsonParser = new JsonParser;
    issues parsedIssues = jsonParser->parseIssues(response.body);

    printAllIssues(parsedIssues);
}

void GetIssueAction::printAllIssues(issues &issuesToPrint) {
    for (issue jiraIssue : issuesToPrint) {
        summary *summaryField = static_cast<summary *>(jiraIssue.fields["summary"]);
        issue_type *issueType = static_cast<issue_type *>(jiraIssue.fields["issuetype"]);
        components *componentsInfo = static_cast<components *>(jiraIssue.fields["components"]);

        std::vector<std::string> componentsNames;
        for (auto component : componentsInfo->components) {
            componentsNames.push_back(component.name);
        }

        std::cout << jiraIssue.key
        << " - "
        << summaryField->summary
        << " <"
        << issueType->name
        << ">"
        << "["
        << StringUtils::join(componentsNames, ',')
        << "]"
        << std::endl;
    }

}
