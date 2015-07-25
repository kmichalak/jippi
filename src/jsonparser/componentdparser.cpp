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
 */

#include <include/jippi/jippi.hpp>
#include "include/jsonparser/componentsparser.hpp"

using namespace jippi;

ComponentsFieldParser::ComponentsFieldParser() { }

ComponentsFieldParser::~ComponentsFieldParser() { }

field *ComponentsFieldParser::parse(Json::Value &fieldJsonDocument) {
    components *componentsInfo = new components;

    if (fieldJsonDocument.isArray()) {

        for (Json::Value::iterator iterator = fieldJsonDocument.begin(); iterator != fieldJsonDocument.end(); iterator++) {
            Json::Value componentJsonDocument = *iterator;
            component componentInfo;
            componentInfo.id = componentJsonDocument["id"].asString();
            componentInfo.self = componentJsonDocument["self"].asString();
            componentInfo.name = componentJsonDocument["name"].asString();

            componentsInfo->components.push_back(componentInfo);
        }

    }

    return componentsInfo;
}
