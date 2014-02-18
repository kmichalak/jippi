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

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <jsoncpp/json/json.h>
#include <exception>
#include "inc/jippi.hpp"

namespace jippi {
	
class JsonParser
{
public:
	issues parseIssues(std::string &jsonDocument);
	
private:
	issues fetchIssuesInfo(Json::Value &issuesJsonDocument);
	issue fetchIssueInfo(Json::Value &issueJsonDocument);
};



class FieldParser 
{
public:
	virtual ~FieldParser() {};
	virtual field * parse(Json::Value &fieldJsonDocument) = 0;
};

class AssigneeFieldParser : public FieldParser 
{
public:
	virtual ~AssigneeFieldParser() {};
	virtual field * parse(Json::Value &fieldJsonDocument);
	virtual avatar_urls fetchAvatarUrlsInfo(Json::Value &avatarUrlJsonDocument);
};

class ReporterFieldParser : public FieldParser 
{
public:
	virtual ~ReporterFieldParser() {};
	virtual field * parse(Json::Value &fieldJsonDocument);
	virtual avatar_urls fetchAvatarUrlsInfo(Json::Value &avatarUrlJsonDocument);
};

class ProjectFieldParser : public FieldParser 
{
public:
	virtual ~ProjectFieldParser () {};
	virtual field * parse(Json::Value &fieldJsonDocument);
private:
	virtual avatar_urls fetchAvatarUrlsInfo(Json::Value &avatarUrlJsonDocument);
};

class IssueTypeFieldParser : public FieldParser 
{
public:
	virtual ~IssueTypeFieldParser() {};
	virtual field * parse(Json::Value &fieldJsonDocument);
};

class ProgressFieldParser : public FieldParser
{
public:
	virtual ~ProgressFieldParser() {};
	virtual field * parse(Json::Value &fieldJsonDocument);
};


class UninitializedParserException : public std::runtime_error
{
public:
	UninitializedParserException(std::string msg) 
		: std::runtime_error(msg)
	{}
};

class IssueParser
{
public:
	virtual ~IssueParser() {};
	virtual void initialize();
	virtual issue parse(Json::Value& issueJsonDocument);
private:
	bool initialized;
 	std::unordered_map<std::string, FieldParser*> fieldsParserRegistry;
};

}; // end of namespace

#endif // JSONPARSER_H
