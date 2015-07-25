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
#include <map>

#include "jippi/action.hpp"
#include "jippi/getissueaction.hpp"

namespace jippi {

#ifndef ARG_HANDLER_CONSTS
#define ARG_HANDLER_CONSTS
    
#define GROUP_SECTION   0    /* Section in pair where grop name is stored */
#define KEY_SECTION     1    /* Second in pair where key name is stored */
    
#endif

#ifndef ACTION_FACTORY_FUNCTION_
#define ACTION_FACTORY_FUNCTION_
    
// Simple abstract factory function
template<typename T> Action * createInstance() { return new T; }

#endif


#ifndef CLASS_MAP_T_
#define CLASS_MAP_T_

// Type definition for action name to class map.
typedef std::map<std::string, Action*(*)()> class_map_t;

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
    
    // Description of the long command line options.
    const struct option long_options[11] = {
        {"help",            no_argument,        0, 'h'},
        {"config",          optional_argument,  0, 'c'},
        {"action",          required_argument,  0, 'A'},
        {"issue",           required_argument,  0, 'i'},
        {"assignee",        required_argument,  0, 'a'},
        {"project",         required_argument,  0, 'p'},
        {"max-results",     required_argument,  0, 'r'},
        {"issue-type",      required_argument,  0, 't'},
        {"debug",           no_argument,        0, 'd'},
        {"labels",          required_argument,  0, 'l'},
        {NULL,              no_argument,        NULL, 0}
    };
    
    // Collection of short options
    const char *short_args = "hc:A:i:a:p:r:t:l:d";
    
    // This map contains pairs ActionName->ActionImplementation.
    // It's used to create valid instance of the action based on the 
    // action name. 
    class_map_t actionToClassMap = {
         {"getIssue", &createInstance<GetIssueAction>}
     };
    
    Action *action;
    
    // methods
    void handleConfiguration();
    void handleAction();
};

} // end of namespace

#endif // COMMANDLINEARGUMENTHANDLER_H
