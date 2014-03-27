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

#include "jsonparser/exception.hpp"
#include "jsonparser/assignee.hpp"
#include "jsonparser/issuetype.hpp"
#include "jsonparser/progress.hpp"
#include "jsonparser/project.hpp"
#include "jsonparser/reporter.hpp"
#include "jsonparser/summaryparser.hpp"
#include "jsonparser/exception.hpp"
#include "jsonparser/issue.hpp"

using namespace jippi;

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
            issueInfo.allFields[key] = issueField;
        }
    }
    
    return issueInfo;
}

void IssueParser::initialize()
{
    fieldsParserRegistry["issuetype"] = new IssueTypeFieldParser();
    fieldsParserRegistry["reporter"] = new ReporterFieldParser();
    fieldsParserRegistry["assignee"] = new AssigneeFieldParser();
    fieldsParserRegistry["project"] = new ProjectFieldParser();
    fieldsParserRegistry["progress"] = new ProgressFieldParser();
    fieldsParserRegistry["summary"] = new SummaryFieldParser();
    initialized = true;
}
