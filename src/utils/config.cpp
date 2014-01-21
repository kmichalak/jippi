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

#include "include/config.h"

#include <iostream>
#include <libconfig.h++>
#include <stdlib.h>
#include <string.h>

jippi::Config::Config(const std::string &configuration_file, 
					  const std::string &configuration_path)
{
	this->configuration_file = configuration_file;
	this->configuration_path = configuration_path;
}

jippi::Config::~Config()
{

}

void jippi::Config::readConfiguration() 
{
	const char* home_dir = getenv("HOME");
	const char* config_file = ".jippiconfig";
	
	std::string config_path = std::string(home_dir) + "/" + std::string(config_file);
	
  	libconfig::Config config;
	try {
		config.readFile(config_path.c_str());
		
		try {
			
 			std::string jira_url = config.lookup("jira_url");
			
		} catch (libconfig::SettingNotFoundException &e) {
			std::cerr << "There was an error during reading configuration from file: " << e.what() << std::endl;
		}
		
		
	} catch(const libconfig::FileIOException &fioex) {
		std::cerr << "I/O error while reading configuration file" << std::endl;
	}
}

std::string jippi::Config::get_property(const std::string& key)
{

}

// Some getters 

std::string jippi::Config::get_file()
{
	return this->configuration_file;
}

std::string jippi::Config::get_path()
{
	return this->configuration_path;
}
