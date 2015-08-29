/*
 * Copyright 2015 Kamil Michalak <kmichalak8@gmail.com>
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
 */

#ifndef JIPPI_STATUS_HPP
#define JIPPI_STATUS_HPP

#include <unordered_map>
#include "fieldparser.hpp"

namespace jippi {

class StatusParser
{
public:
    virtual ~StatusParser() {}
    virtual void initialize();
    virtual status parse(Json::Value& statusJsonDocument);
private:
    bool initialized;
    std::unordered_map<std::string, FieldParser*> fieldsParserRegistry;
};

}

#endif //JIPPI_STATUS_HPP
