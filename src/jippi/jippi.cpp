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

#include <cstdlib>        // free support
#include <string.h>
#include <sstream>

#include "jippi/jippi.hpp"

using namespace jippi;

EmptyConfigurationValueException::EmptyConfigurationValueException()
{
    configurationGroupName = "";
    configurationValueName = "";
}

EmptyConfigurationValueException::EmptyConfigurationValueException(std::string configGroup, std::string configProperty)
{
    configurationGroupName = configGroup;
    configurationValueName = configProperty;

}

EmptyConfigurationValueException::~EmptyConfigurationValueException() throw()
{

}

std::string EmptyConfigurationValueException::what()
{
    std::ostringstream messageStream;
    messageStream << this->configurationGroupName << "." << this->configurationValueName;
    return messageStream.str();
}

InvalidQueryException::InvalidQueryException(std::string message) {
    this->message = message;
}

InvalidQueryException::~InvalidQueryException() throw() {}

std::string InvalidQueryException::what() {
    return message;
}
