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
#include <bits/stl_set.h>
#include <algorithm>        // for_each
#include <iostream>
#include <bits/stream_iterator.h>

#include "stringutils/stringutils.hpp"
#include "jippi/config.hpp"
#include "restclient/restclient.hpp"

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
        configuration = new Config(DEFAULT_CONFIG_FILE, DEFAULT_CONFIG_FILE_LOCATION);
        configuration->readConfigurationFromFile();
        restClient = new RestClient();
    }

    virtual ~Action() {
        delete restClient;
        delete configuration;
    }
    
    //-----------------------------------------------------------
    // JSON fields
    //-----------------------------------------------------------
    
    inline void withStartAt(int startAt)
    {
        json["startAt"] = startAt;
    }
    
    inline void withMaxResults(int maxResults)
    {
        assert(maxResults > 0 && "Max number of results should be greater than 0!");
        json["maxResults"] = maxResults;
    }
    
    inline void withFields(std::string fields)
    {
        assertValidStringParam(fields, "List of fields cannot be an empty string!");
        json["fields"] = fields;
    }
    
    //-----------------------------------------------------------
    // JSQL elements
    //-----------------------------------------------------------
    
    inline void withProject(std::string project)
    {
        assertValidStringParam(project, "Project ID cannot be an empty string!");
        appendToQuery("project = " + project);
    }
    
    inline void withIssue(std::string issue) 
    {
        assertValidStringParam(issue, "Issue ID cannot be an empty string!");
        appendToQuery("issue = " + issue);
    }
        
    inline void withAssignee(std::string assignee)
    {
        assertValidStringParam(assignee, "Assignee ID cannot be an empty string!");
        appendToQuery("assignee = \"" + assignee + "\"");
    }
    
    inline void withIssueTypeName(std::string issueType) 
    {
        assertValidStringParam(issueType, "Issue type name cannot be an empty string!");
        // We have to escape issue type because some users set those values to something like "User Story",
        // "Story bug" or something similar...
        appendToQuery("issueType = " + escapeStringValue(issueType));
    }

    inline std::string escapeStringValue(std::string issueType) {
        return "\"" + issueType + "\"";
    }

    inline void withLabels(std::string labels)
    {
        const std::vector<std::string> &separatedLabels = StringUtils::split(labels, ',');
        std::string result = StringUtils::join(separatedLabels, ',');
        appendToQuery("labels in (" + result + ")");
    }

    // others 
    
    inline void debug(bool isInDebugMode)
    {
        this->isInDebugMode = isInDebugMode;
    }
    
    virtual void perform() {}
    
protected:
    Config *configuration;
    RestClient *restClient;
    std::string getJSONPayload()
    {
        if (Json::Value::null == json) {
            return "";
        }
        std::string payload = jsonWriter.write(json);
        return payload;
    }
    bool isInDebugMode = false;
private:
    Json::StyledWriter jsonWriter;
    Json::Value json;
    
    inline void assertValidStringParam(std::string str, std::string msg)
    {
        assert(!jippi::StringUtils::isEmpty(str) && msg.c_str());
    }
    
    inline void appendToQuery(std::string valueToAppend)
    {
        if (StringUtils::isEmpty(this->json["jql"].asString())) {
            this->json["jql"] = valueToAppend;
        } else {
            this->json["jql"] = this->json["jql"].asString() + " AND " + valueToAppend;
        }
    }
};

} // end of namespace

#endif // ACTION_H
