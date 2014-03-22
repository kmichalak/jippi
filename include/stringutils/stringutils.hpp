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

#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <string>
#include <vector>

namespace jippi {
    
class StringUtils
{
public:
    static std::string trim(const std::string & str);
    static bool isEmpty(const std::string & str);
    
    static std::vector<std::string> split(const std::string &s, char delim);
private: 
    static std::string rightTrim(const std::string & str);
    static std::string leftTrim(const std::string & str);
    
    static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
};


} // end of namespace

#endif // STRINGUTILS_H
