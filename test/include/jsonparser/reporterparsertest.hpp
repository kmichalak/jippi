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

#ifndef ASSIGNEEPARSERTEST_H
#define ASSIGNEEPARSERTEST_H

#include <gtest/gtest.h>

class ReporterParserTest : public testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();
    
    const std::string REPORTER_JSON = 
        "{\"self\":\"http://test.jira.org/rest/api/2/user?username=Test.Reporter\","
        "\"name\":\"Test.Reporter\",\"emailAddress\":\"test.reporter@test.org\","
        "\"avatarUrls\":{\"16x16\":"
        "\"http://test.jira.org/secure/useravatar?size=xsmall&ownerId=test.reporter&avatarId=12726\","
        "\"24x24\":\"http://test.jira.org/secure/useravatar?size=small&ownerId=test.reporter&avatarId=12726\","
        "\"32x32\":\"http://test.jira.org/secure/useravatar?size=medium&ownerId=test.reporter&avatarId=12726\","
        "\"48x48\":\"http://test.jira.org/secure/useravatar?ownerId=test.reporter&avatarId=12726\"},"
        "\"displayName\":\"Reporter, Test\",\"active\":true}";
};

#endif // ASSIGNEEPARSERTEST_H
