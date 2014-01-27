/*
 * Copyright 2013 Kamil Michalak <kmichalak8@gmail.com>
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

#include "inc/stringutils.hpp"
#include <string>
#include <sstream>

using namespace jippi;

std::string StringUtils::trim(const std::string& str)
{
	return leftTrim(rightTrim(str));
}

std::string StringUtils::leftTrim(const std::string& str)
{
	std::string::size_type pos = str.find_first_not_of(' ');
	if (pos == std::string::npos) {
		return std::string();
	}
	return str.substr(pos, std::string::npos);
}

std::string StringUtils::rightTrim(const std::string& str)
{
	std::string::size_type pos = str.find_last_not_of(' ');
	if (pos == std::string::npos) {
		return std::string();
	}
	return str.substr(0, pos + 1);
}

bool StringUtils::isEmpty(const std::string & str)
{
	return str.length() == 0;
}

std::vector<std::string> StringUtils::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::vector<std::string> & StringUtils::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
