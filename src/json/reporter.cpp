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

#include "inc/json/reporter.hpp"

using namespace jippi;

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
