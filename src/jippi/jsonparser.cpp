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
#include <string>
#include <unordered_map>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

#include "jippi/jsonparser.hpp"
#include "json/issue.hpp"

using namespace jippi;

issues JsonParser::parseIssues(std::string &jsonDocument)
{
    Json::Value root;
    Json::Reader jsonReader;
    bool parseSuccess = jsonReader.parse(jsonDocument, root, false);
    
    if (! parseSuccess) {
        
    }
    Json::Value issuesJsonDocument = root["issues"];
    issues issuesCollection = fetchIssuesInfo(issuesJsonDocument);
    return issuesCollection;
}

issues JsonParser::fetchIssuesInfo(Json::Value& issuesJsonDocument)
{
    issues issuesCollection;
    IssueParser *issueParser = new IssueParser();
     issueParser->initialize();
    if (issuesJsonDocument.isArray()) {
        for (unsigned int index=0; index < issuesJsonDocument.size(); index++) {
            Json::Value issueJsonDocument = issuesJsonDocument[index];
            issue issueInfo = issueParser->parse(issueJsonDocument);
            issuesCollection.push_back(issueInfo);
        }
    }
    delete issueParser;
    return issuesCollection;
}

issue JsonParser::fetchIssueInfo(Json::Value& issueJsonDocument)
{
    issue issueContainer;
    
    issueContainer.id = issueJsonDocument["id"].asString();
    issueContainer.key = issueJsonDocument["key"].asString();
    issueContainer.self = issueJsonDocument["self"].asString();
        
    return issueContainer;
}
