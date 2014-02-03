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

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>		// std::string
#include <libconfig.h++>	// libconfig::Config
#include <map>

#ifndef CONFIGURATION_DEFAULTS
#define CONFIGURATION_DEFAULTS

const std::string DEFAULT_CONFIG_FILE = "jippi.config";
const std::string DEFAULT_CONFIG_FILE_LOCATION = "./";

const std::string JIRA_GROUP = "jira";
const std::string JIRA_URL = "url";
const std::string JIRA_USER = "user";
const std::string JIRA_PASSWORD = "password";

const std::map<std::string, std::string> DEFAULT_JIRA_CONFIGURATION = {
	{"url", 		""},
	{"user", 		""},
	{"password", 	""}
};

#endif

namespace jippi {

class Config
{
public:
	Config(const std::string configuration_file, const std::string configuration_path);
	~Config();
	
	// methods
	bool foundConfigurationFile();
	void storeDefaultConfigurationInFile();
	
	void readConfigurationFromFile();
	void writeConfigurationToFile();
	
	void storeProperty(const std::string &group, const std::string &key, const std::string &value);
	std::string getProperty(const std::string &group, const std::string &key);
	std::string getFileName();
	
private:	
	// variables
	libconfig::Config *configuration;
	std::string configuration_file;
	
	void easy_init();
	
	/**
	 * Helper class used to write default configuration to the file.
	 */
	class StorePropertyFunction {
	public:
		StorePropertyFunction(Config *configuration, std::string group) { 
			this->group = group;
			this->configuration = configuration;
		}
		
		~StorePropertyFunction() {
			this->configuration = NULL;
		}
		
		void operator() (std::pair<std::string, std::string> pair) { 
			configuration->storeProperty(group, pair.first, pair.second);
		}
		
	private:
		Config *configuration;
		std::string group; 
	};
	
};

}	// namespace

#endif // CONFIG_H
