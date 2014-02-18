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
#ifndef ISSUE_H
#define ISSUE_H

#include <unordered_map>
#include "inc/json/fieldparser.hpp"

namespace jippi {

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

}

#endif
