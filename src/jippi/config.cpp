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

#include "jippi/config.hpp"

#include <libconfig.h++>    // support for configuration files 
#include <unistd.h>         // stat
#include <algorithm>        // for_each

using namespace jippi;

Config::Config(const std::string configuration_file, const std::string configuration_path)
{
    this->configuration_file = configuration_path + configuration_file;
    this->configuration = new libconfig::Config;
    if (!foundConfigurationFile()) {
        storeDefaultConfigurationInFile();
    }
}


Config::~Config()
{
    delete this->configuration;
}


bool Config::foundConfigurationFile() 
{
    return access(configuration_file.c_str(), 0) == F_OK;
}


void Config::storeDefaultConfigurationInFile()
{
    // Add all values from default Jira configuration 
    StorePropertyFunction *store_property = new StorePropertyFunction(this, JIRA_GROUP);
    std::for_each(DEFAULT_JIRA_CONFIGURATION.begin(), DEFAULT_JIRA_CONFIGURATION.end(), *store_property);
    delete store_property;
    // Write configuration to the file
    writeConfigurationToFile();
}


void Config::readConfigurationFromFile()
{    
    try {
        configuration->readFile(configuration_file.c_str());
    } catch(const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading configuration file " << configuration_file << std::endl;
        std::cerr << fioex.what();
    }
}


void Config::writeConfigurationToFile()
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


std::string Config::getProperty(const std::string &group, const std::string& key)
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


void Config::storeProperty(const std::string &group, const std::string &key, const std::string &value)
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
std::string Config::getFileName()
{
    return this->configuration_file;
}
