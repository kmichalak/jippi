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

#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <assert.h>
#include <jsoncpp/json/json.h>

#include "inc/stringutils.hpp"

namespace jippi {

/**
 * An abstract class representing basic Jira command line client action.
 * This class should be used as a base for further actions such as getting,
 * creating, deleting issues, etc.
 * 
 * Current implementation allows to specify 
 */
class Action
{
public:
	Action() {
	}
	
	virtual ~Action() {
	};
	
	inline void withIssue(std::string issue) 
	{
		assertValidStringParam(issue, "Issue ID cannot be an empty string!");
		this->issue = issue;
		json["issue"] = issue;
	}
	
	inline void withProject(std::string project)
	{
		assertValidStringParam(project, "Project ID cannot be an empty string!");
		this->project = project;
		this->json["jql"] = "project=" + project;
	}
	
	inline void withAssignee(std::string assignee)
	{
		assertValidStringParam(assignee, "Assignee ID cannot be an empty string!");
		this->assignee = assignee;
		json["assignee"] = assignee;
	}
	
	virtual void perform() {};
	
protected:
	std::string issue;
	std::string project;
	std::string assignee;
	
	std::string getJSONPayload()
	{
		std::string payload = jsonWriter.write(json);
		return payload;
	}
	
private:
	Json::StyledWriter jsonWriter;
	Json::Value json;
	
	inline void assertValidStringParam(std::string str, std::string msg)
	{
		assert(!jippi::StringUtils::isEmpty(str) && msg.c_str());
	}
};

}; // end of namespace

#endif // ACTION_H
