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

#include <unistd.h>
#include <stdio.h>
#include <gtest/gtest.h>
#include "configtest.hpp"

#include "../inc/config.hpp"

void ConfigTest::SetUp()
{
	config_file = "test.conf";
	config_path = "./";
}

void ConfigTest::TearDown()
{
	// delete file if it exists
	std::string file = config_path + config_file;
	if (access(file.c_str(), 0) == F_OK) {
		int status = remove(file.c_str());
		if (status != 0) {
			FAIL() << "Cannot delete test configuration file";
		}
	}
}

TEST_F(ConfigTest, ConstructorCreatesValidConfigurationObject)
{
	// when
	jippi::Config *conf = new jippi::Config(config_file, config_path);
	
	// then
	EXPECT_EQ(config_path + config_file, conf->get_file());
	
	// cleanup
 	delete conf;
}

TEST_F(ConfigTest, StorePropertySavesValue)
{
	// given 
	const std::string value = "test_value";
	const std::string group = "test_group";
	const std::string key = "test_property";
	
	// when
	jippi::Config *conf = new jippi::Config(config_file, config_path);
	conf->store_property(group, key, value);
	conf->writeConfiguration();
	
	conf->readConfiguration();
	std::string config_value = conf->get_property(group, key);
	
	// then
	EXPECT_EQ(value, config_value);
	
	// cleanup
	delete conf;
}