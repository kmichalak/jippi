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

#ifndef JIPPI_H
#define JIPPI_H

#include <string>
#include <vector>
#include <exception>

namespace jippi {
    
#ifndef __json_members
#define __json_members

    
typedef struct {
    std::string id;            /* field ID */ 
    std::string self;        /* field definition URL */
    std::string description;    /* field description */ 
    std::string name;        /* field custom name */ 
} field;        


typedef std::vector<field> fields;


typedef struct {
    std::string size16x16;        /* 16x16 pixels */
    std::string size24x24;        /* 24x24 pixels */
    std::string size32x32;        /* 32x32 pixels */
    std::string size48x48;        /* 48x48 pixels */
} avatar_urls;


typedef struct : field {
    std::string emailAddress;    /* e-mail addrress of the issue reporter*/
    std::string displayName;    /* name of the reporter to display */ 
    bool active;            /* reporter account is active */ 
    avatar_urls avatarUrls;        /* reporter avatars */
} reporter;


typedef struct : field {
    std::string emailAddress;    /* e-mail address of the assignee */
    std::string displayName;    /* assignee display name */
    bool active;            /* account active */ 
    avatar_urls avatarUrls;        /* assignee avatars */
} assignee;


typedef struct : field {
    std::string key;
    avatar_urls avatarUrls;
} project;


typedef struct : field {
    std::string iconUrl;
} status;


typedef struct : field {
    long progress;            /* isse reported progress */
    long total;            /* total planned progress for issue */
    long percent;            /* issue reported progress percentage */
} progress;


typedef struct : field {
    std::string iconUrl;        /* issue type icon URL */
    bool subtask;            /* issue is a subtask */
} issue_type;


typedef struct {
    std::string id;            /* issue ID */ 
    std::string self;        /* issue definition URL */ 
    std::string key;        /* issue key */     
    fields fieldsCollection;    /* collection of fieds assigned to the issue */ 
} issue;


typedef std::vector<issue> issues;


#endif


class ConfigurationException : public std::exception { };

class EmptyConfigurationValueException : public ConfigurationException
{
public:
    EmptyConfigurationValueException();
    EmptyConfigurationValueException(const char *name);
    virtual ~EmptyConfigurationValueException() throw();
    
private:
    char *configurationValueName;
};

}; // end of namespace

#endif // GETISSUEACTION_H
