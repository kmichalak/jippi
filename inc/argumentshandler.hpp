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

#ifndef ARGUMENTSHANDLER_HPP
#define ARGUMENTSHANDLER_HPP

#include <stddef.h>
#include <getopt.h>

namespace jippi {

#ifndef ARG_HANDLER_CONSTS
#define ARG_HANDLER_CONSTS
	
#define GROUP_SECTION 	0	/* Section in pair where grop name is stored */
#define KEY_SECTION 	1	/* Second in pair where key name is stored */
	
#endif
	
class ArgumentsHandler
{
public:
	ArgumentsHandler(int argc, char **argv);
	virtual ~ArgumentsHandler();
	
	void handle();
	
private:
	int argumentsCounter;
	char **argumentsVector;
	const struct option long_options[3] = {
		{"config", 1, 0, 'c'},
		{"help", 0, 0, 'h'},
		{NULL, 0, NULL, 0}
	};
	
	// methods
 	void handleConfiguration();
};

}; // end of namespace

#endif // COMMANDLINEARGUMENTHANDLER_H
