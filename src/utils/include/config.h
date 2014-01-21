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

#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>

namespace jippi {

class Config
{
public:
	Config(const std::string &configuration_file, 
		   const std::string &configuration_path);
	~Config();
	
	// methods
	std::string get_file();
	std::string get_path();
	std::string get_property(const std::string &key);
private:
	void readConfiguration();
	void writeConfiguration();
	
	// variables
	std::string configuration_path;
	std::string configuration_file;
};

}	// namespace

#endif // CONFIG_H
