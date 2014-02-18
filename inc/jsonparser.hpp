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

#include <string>

#include "inc/json/assignee.hpp"
#include "inc/json/fieldparser.hpp"
#include "inc/json/issue.hpp"
#include "inc/json/issuetype.hpp"
#include "inc/json/progress.hpp"
#include "inc/json/project.hpp"
#include "inc/json/reporter.hpp"
#include "inc/json/exception.hpp"

#include <jsoncpp/json/value.h>

namespace jippi {
    
class JsonParser
{
public:
    issues parseIssues(std::string &jsonDocument);
    
private:
    issues fetchIssuesInfo(Json::Value &issuesJsonDocument);
    issue fetchIssueInfo(Json::Value &issueJsonDocument);
};

}; // end of namespace

#endif // JSONPARSER_H
