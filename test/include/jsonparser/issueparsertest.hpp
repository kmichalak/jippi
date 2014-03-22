/*
 * Copyright 2014 <copyright holder> <email>
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

#ifndef ISSUEPARSERTEST_H
#define ISSUEPARSERTEST_H

#include <gtest/gtest.h>

class IssueParserTest : public testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();
    
    std::string ISSUE_JSON = "{\"expand\":\"editmeta,renderedFields,transitions,"
        "changelog,operations\",\"id\":\"TEST_ID\",\"self\":"
        "\"http://test.jira.org\",\"key\":\"TEST-1\",\"fields\":"
        "{\"issuetype\":{\"self\":\"http://test.jira.org/rest/api/2/issuetype/7\","
        "\"id\":\"7\",\"description\":\"A user story\",\"iconUrl\":"
        "\"http://test.jira.org/images/icons/issuetypes/story.png\",\"name\":"
        "\"Story\",\"subtask\":false},\"project\":{\"self\":"
        "\"http://test.jira.org/rest/api/2/project/TEST\",\"id\":\"12633\","
        "\"key\":\"TEST\",\"name\":\"Test Project\",\"avatarUrls\":"
        "{\"16x16\":\"http://test.jira.org/secure/projectavatar?size=xsmall&pid=12633&avatarId=12734\","
        "\"24x24\":\"http://test.jira.org/secure/projectavatar?size=small&pid=12633&avatarId=12734\","
        "\"32x32\":\"http://test.jira.org/secure/projectavatar?size=medium&pid=12633&avatarId=12734\","
        "\"48x48\":\"http://test.jira.org/secure/projectavatar?pid=12633&avatarId=12734\"}}}}";
};

#endif // ISSUEPARSERTEST_H
