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

#include <include/jippi/jippi.hpp>
#include <include/restclient/restclient.hpp>
#include "jippi/getstatusesaction.hpp"

#include "jippi/jsonparser.hpp"

using namespace jippi;

GetStatusesAction::GetStatusesAction() {}

GetStatusesAction::~GetStatusesAction() {}

void GetStatusesAction::perform() {
    rest_response response = performHttpGetRequest("/status");
    JsonParser *jsonParser = new JsonParser();
    std::cout << response.body << std::endl;
    const statuses &statusesInfo = jsonParser->parseStatuses(response.body);
    delete jsonParser;

    if (statusesInfo.size() == 0) {
        std::cout << "No statuses found"<< std::endl;
    }
    for (status statusInfo : statusesInfo) {
        std::cout << statusInfo.name << std::endl;
    }

}