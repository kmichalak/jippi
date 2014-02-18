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
#ifndef ASSIGNEE_H
#define ASSIGNEE_H

#include "inc/json/fieldparser.hpp"

namespace jippi {

class AssigneeFieldParser : public FieldParser 
{
public:
	virtual ~AssigneeFieldParser() {};
	virtual field * parse(Json::Value &fieldJsonDocument);
	virtual avatar_urls fetchAvatarUrlsInfo(Json::Value &avatarUrlJsonDocument);
};

}

#endif
