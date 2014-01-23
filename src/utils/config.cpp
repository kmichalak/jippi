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

#include "../../inc/config.hpp"

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <libconfig.h++>
#include <iomanip>

#include <unistd.h>	// stat

jippi::Config::Config(const std::string &configuration_file, 
					  const std::string &configuration_path)
{
	this->configuration_file = configuration_path + configuration_file;
	this->configuration = new libconfig::Config;
}

jippi::Config::~Config()
{
	delete this->configuration;
}

void jippi::Config::readConfiguration()
{	
	try {
		configuration->readFile(configuration_file.c_str());
	} catch(const libconfig::FileIOException &fioex) {
		std::cerr << "I/O error while reading configuration file " << configuration_file << std::endl;
		std::cerr << fioex.what();
	}
}

void jippi::Config::writeConfiguration()
{
	try {
		if (configuration != NULL) {
			configuration->writeFile(configuration_file.c_str());
		}
	} catch (const libconfig::FileIOException &fioex) {
		std::cout << "I/O error while writing configuration file " << configuration_file << std::endl;
		std::cout << fioex.what() << std::endl;
	}
}


std::string jippi::Config::get_property(const std::string &group, 
										const std::string& key)
{
	libconfig::Setting &root = configuration->getRoot();
	if (root.exists(group)) {
		libconfig::Setting &config_group = root[group];
		if (config_group.exists(key)) {
			return config_group[key];
		}
	}
	return NULL;
}

void jippi::Config::store_property(const std::string &group, 
								   const std::string &key, 
								   const std::string &value)
{
	libconfig::Setting &root = configuration->getRoot();
	// Check if there is property with given name. If not then create one.
	if (!root.exists(group)) {
		root.add(group, libconfig::Setting::TypeGroup);
	}
	
	libconfig::Setting &config_group = root[group];
	if (!config_group.exists(key)) {
		config_group.add(key, libconfig::Setting::TypeString) = value;
	} else {
		config_group[key] = value;
	}
}

// Some getters 

std::string jippi::Config::get_file()
{
	return this->configuration_file;
}
