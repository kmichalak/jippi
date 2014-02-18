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
#include <jsoncpp/json/json.h>
#include "inc/jsonparser.hpp"

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


issue IssueParser::parse(Json::Value& issueJsonDocument)
{
	if (fieldsParserRegistry.size() == 0) {
		throw UninitializedParserException("Uninitialized parser: IssueParser");
	}
	
	issue issueInfo;
	
	issueInfo.id = issueJsonDocument["id"].asString();
	issueInfo.key = issueJsonDocument["key"].asString();
	issueInfo.self = issueJsonDocument["self"].asString();
	
	Json::Value fieldsJsonDocument = issueJsonDocument["fields"];
	
	Json::Value::Members fields = fieldsJsonDocument.getMemberNames();
	Json::Value::Members::iterator fieldsIterator;
	
	for (fieldsIterator = fields.begin(); fieldsIterator != fields.end(); fieldsIterator++) {
		std::string key = *fieldsIterator;
 		std::unordered_map<std::string, FieldParser*>::const_iterator found = fieldsParserRegistry.find(key);
		bool foundItem = found != fieldsParserRegistry.end();
		if (foundItem) {
			FieldParser * fieldParser = static_cast<FieldParser *>(fieldsParserRegistry[*fieldsIterator]);
			field * issueField = fieldParser->parse(fieldsJsonDocument[*fieldsIterator]);
			issueInfo.fieldsCollection.push_back(*issueField);
		} else {
			std::cerr << "Cannot find parser for field " << key << std::endl;
		}
		
	}
	
	return issueInfo;
}


issue JsonParser::fetchIssueInfo(Json::Value& issueJsonDocument)
{
	issue issueContainer;
	
	issueContainer.id = issueJsonDocument["id"].asString();
	issueContainer.key = issueJsonDocument["key"].asString();
	issueContainer.self = issueJsonDocument["self"].asString();
		
	return issueContainer;
}

void IssueParser::initialize()
{
	fieldsParserRegistry["issueType"] = new IssueTypeFieldParser();
	fieldsParserRegistry["reporter"] = new ReporterFieldParser();
	fieldsParserRegistry["assignee"] = new AssigneeFieldParser();
	fieldsParserRegistry["project"] = new ProjectFieldParser();
	fieldsParserRegistry["progress"] = new ProgressFieldParser();
	initialized = true;
}

field * AssigneeFieldParser::parse(Json::Value& fieldJsonDocument)
{
	assignee *assigneeInfo = new assignee;
	
	assigneeInfo->id = fieldJsonDocument["id"].asString();
	assigneeInfo->self = fieldJsonDocument["self"].asString();
	assigneeInfo->name = fieldJsonDocument["name"].asString();
	assigneeInfo->displayName = fieldJsonDocument["displayName"].asString();
	assigneeInfo->emailAddress = fieldJsonDocument["emailAddress"].asString();
	assigneeInfo->description = fieldJsonDocument["description"].asString();
	assigneeInfo->active = fieldJsonDocument["active"].asBool();
	
	Json::Value avatarUrlJsonDocument = fieldJsonDocument["avatarUrls"];
 	assigneeInfo->avatarUrls = fetchAvatarUrlsInfo(avatarUrlJsonDocument);
	
	return assigneeInfo;
}

avatar_urls AssigneeFieldParser::fetchAvatarUrlsInfo(Json::Value& avatarUrlJsonDocument)
{
	avatar_urls avatarUrls;
	avatarUrls.size16x16 = avatarUrlJsonDocument["16x16"].asString();
	avatarUrls.size24x24 = avatarUrlJsonDocument["24x24"].asString();
	avatarUrls.size32x32 = avatarUrlJsonDocument["32x32"].asString();
	avatarUrls.size48x48 = avatarUrlJsonDocument["48x48"].asString();
	return avatarUrls;
}


field * ProjectFieldParser::parse(Json::Value& fieldJsonDocument)
{
	project *projectInfo = new project;
	
	projectInfo->id = fieldJsonDocument["id"].asString();
	projectInfo->self = fieldJsonDocument["self"].asString();
	projectInfo->name = fieldJsonDocument["name"].asString();
	projectInfo->key = fieldJsonDocument["key"].asString();
		
	Json::Value avatarUrlJsonDocument = fieldJsonDocument["avatarUrls"];
 	projectInfo->avatarUrls = fetchAvatarUrlsInfo(avatarUrlJsonDocument);
	
	return projectInfo;
}

avatar_urls ProjectFieldParser::fetchAvatarUrlsInfo(Json::Value& avatarUrlJsonDocument)
{
	avatar_urls avatarUrls;
	avatarUrls.size16x16 = avatarUrlJsonDocument["16x16"].asString();
	avatarUrls.size24x24 = avatarUrlJsonDocument["24x24"].asString();
	avatarUrls.size32x32 = avatarUrlJsonDocument["32x32"].asString();
	avatarUrls.size48x48 = avatarUrlJsonDocument["48x48"].asString();
	return avatarUrls;
}


field * IssueTypeFieldParser::parse(Json::Value& fieldJsonDocument)
{
	issue_type *issueType = new issue_type;
	
	issueType->id = fieldJsonDocument["id"].asString();
	issueType->self = fieldJsonDocument["self"].asString();
	issueType->name = fieldJsonDocument["name"].asString();
	issueType->description = fieldJsonDocument["description"].asString();
	issueType->iconUrl = fieldJsonDocument["iconUrl"].asString();
	issueType->subtask = fieldJsonDocument["subtask"].asBool();
	
	return issueType;
}

field * ReporterFieldParser::parse(Json::Value& fieldJsonDocument)
{
	reporter *reporterInfo = new reporter;
	
	reporterInfo->id = fieldJsonDocument["id"].asString();
	reporterInfo->self = fieldJsonDocument["self"].asString();
	reporterInfo->name = fieldJsonDocument["name"].asString();
	reporterInfo->displayName = fieldJsonDocument["displayName"].asString();
	reporterInfo->emailAddress = fieldJsonDocument["emailAddress"].asString();
	reporterInfo->description = fieldJsonDocument["description"].asString();
	reporterInfo->active = fieldJsonDocument["active"].asBool();
	
	Json::Value avatarUrlJsonDocument = fieldJsonDocument["avatarUrls"];
 	reporterInfo->avatarUrls = fetchAvatarUrlsInfo(avatarUrlJsonDocument);
	
	return reporterInfo;
}

avatar_urls ReporterFieldParser::fetchAvatarUrlsInfo(Json::Value& avatarUrlJsonDocument)
{
	avatar_urls avatarUrls;
	avatarUrls.size16x16 = avatarUrlJsonDocument["16x16"].asString();
	avatarUrls.size24x24 = avatarUrlJsonDocument["24x24"].asString();
	avatarUrls.size32x32 = avatarUrlJsonDocument["32x32"].asString();
	avatarUrls.size48x48 = avatarUrlJsonDocument["48x48"].asString();
	return avatarUrls;
}

field * ProgressFieldParser::parse(Json::Value& fieldJsonDocument)
{
	progress *progressInfo = new progress;
	
	progressInfo->total = fieldJsonDocument["total"].asInt();
	progressInfo->percent = fieldJsonDocument["percent"].asInt();
	progressInfo->progress = fieldJsonDocument["progress"].asInt();
	
	return progressInfo;
}


