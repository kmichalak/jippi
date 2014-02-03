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

#include <iostream>
#include <vector>

#include "inc/argumentshandler.hpp"
#include "inc/help.hpp"
#include "inc/config.hpp"
#include "inc/stringutils.hpp"

using namespace jippi;

ArgumentsHandler::ArgumentsHandler(int argc, char **argv)
{
	this->argumentsCounter = argc;
	this->argumentsVector = argv;
}

ArgumentsHandler::~ArgumentsHandler()
{

}

void ArgumentsHandler::handle()
{
	int arg_char;
	int option_index = 0;
	if (argumentsCounter > 1) {
		while ((arg_char = getopt_long(argumentsCounter, argumentsVector, short_args, long_options, &option_index)) != -1) {
			switch (arg_char)
			{
				case 0:
					std::cout << long_options[option_index].name << std::endl;
				case 'c': 
					handleConfiguration();
					break;
				case 'A':
					handleAction();
					break;
				case 'a':
					action->withAssignee(optarg);
					break;
				case 'p':
					action->withProject(optarg);
					break;
				case 'i':
					action->withIssue(optarg);
					break;
				case 'r':
					action->withMaxResults(static_cast<int>(*optarg));
					break;
				case 't':
					action->withIssueTypeName(optarg);
					break;
				case 'h': 
					printHelp();
					break;
				default:
					printHelp();
					break;
			}
		} 
	} else { 
		printHelp(); 
	}
	if (action) {
		action->perform();
		delete action;
	}
}

void ArgumentsHandler::handleConfiguration()
{
	if (optarg) {
		// Split configuration parameters using '.' full stop character
		std::vector<std::string> sections = jippi::StringUtils::split(optarg, '.');
		// We are going to set only one value at a time.
		// If there are more than one value, then 
		// there is something wrong.
		if (sections.size() == 2) {
			jippi::Config *configuration = new jippi::Config(DEFAULT_CONFIG_FILE, DEFAULT_CONFIG_FILE_LOCATION);
			std::string group = sections.at(GROUP_SECTION);
			std::string key = sections.at(KEY_SECTION);
			configuration->readConfigurationFromFile();
			configuration->storeProperty(group, key, argumentsVector[optind]);
			configuration->writeConfigurationToFile();
			delete configuration;
		} else {
			std::cerr << "We've got wrong config command" << std::endl;
		}
	} else {
		// Invalid configuration parameters
		printHelp();
	}
}


void ArgumentsHandler::handleAction()
{
	// optarg have to be specified - it contains the name of the action
	if (optarg) {
		action = actionToClassMap[optarg]();
	} else {
		// throw an exception and/or print help 
	}
}
