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
 */

#ifndef HELP_HPP
#define HELP_HPP

#include <iostream>

void printHelp()
{
    const char* HELP_MSG = 
    "\n"                                
    "usage jippi [-h|--help] [-c|--config group.name value] \n"
    "[-A|--action action] [-a|--assignee assignee] [-i|--issue issue] \n"
    "[-p|--project project]    [-r|--max-results] [-t|--issue-type] \n"
    "Arguments:\n"
    "\n\t -A, --action action     \t Specify action name to perform"     
    "\n\t -a, --assignee assignee\t Name of the issue assignee"    
    "\n\t -i, --issue issue    \t Issue identifier"
    "\n\t -p, --project project    \t Project name"
    "\n\t -r, --max-results    \t Maximun number of results returned by query"
    "\n\t -t, --issue-type     \t Expected type of issues"
    "\n";
    
    std::cout << HELP_MSG << std::endl;
}

#endif
