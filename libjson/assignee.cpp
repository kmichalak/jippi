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
#include "inc/jippi.hpp"
#include "exception.hpp"
#include "assignee.hpp"


using namespace jippi;

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