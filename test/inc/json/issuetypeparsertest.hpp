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

#ifndef ISSUETYPEPARSERTEST_H
#define ISSUETYPEPARSERTEST_H

#include <gtest/gtest.h>

class IssueTypeParserTest : public testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();
    
    const std::string ISSUE_TYPE_JSON = "{"
          "\"self\": \"http://test.jira.org/rest/api/2/issuetype/7\","
          "\"id\": \"TEST-ID\","
          "\"description\": \"TEST-DESCRIPTION\","
          "\"iconUrl\": \"http://test.jira.org/images/icons/issuetypes/story.png\","
          "\"name\": \"TEST-NAME\","
          "\"subtask\": false"
        "}";
};

#endif // ISSUETYPEPARSERTEST_H
