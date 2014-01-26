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
#include <getopt.h>
#include <vector>

#include "inc/stringutils.hpp"
#include "inc/config.hpp"
#include "inc/help.hpp"



int main(int argc, char **argv)
{	
	int arg_char;
	
	static struct option long_options[] = {
		{"config", 1, 0, 'c'},
		{"help", 0, 0, 'h'},
		{NULL, 0, NULL, 0}
	};
	
	
	int option_index = 0;
	if (argc > 1) {
		while ((arg_char = getopt_long(argc, argv, "hc:", long_options, &option_index)) != -1) {
			switch (arg_char)
			{
				case 0:
					std::cout << long_options[option_index].name << std::endl;
				case 'c': 
					if (optarg) {
						// Split configuration parameters using '.' full stop character
						std::vector<std::string> sections = jippi::StringUtils::split(optarg, '.');
						// We are going to set only one value at a time.
						// If there are more than one value, then 
						// there is something wrong.
						if (sections.size() == 2) {
							jippi::Config *configuration = new jippi::Config(DEFAULT_CONFIG_FILE, DEFAULT_CONFIG_FILE_LOCATION);
							if (!configuration->foundConfigurationFile()) {
								configuration->storeDefaultConfigurationInFile();
							}
							std::string group = sections.at(0);
							std::string key = sections.at(1);
							configuration->readConfigurationFromFile();
							configuration->storeProperty(group, key, argv[optind]);
							configuration->writeConfigurationToFile();
							delete configuration;
						} else {
							std::cerr << "We've got wrong config command" << std::endl;
						}
					} else {
						// Invalid configuration parameters
						printHelp();
					}
						
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
	return 0;
}
