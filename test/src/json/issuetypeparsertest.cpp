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
#include <jsoncpp/json/reader.h>
#include "json/issuetype.hpp"
#include "test/include/json/issuetypeparsertest.hpp"

void IssueTypeParserTest::SetUp()
{

}

void IssueTypeParserTest::TearDown()
{

}

TEST_F(IssueTypeParserTest, ShouldContainValidSelfInfo) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_TYPE_JSON, root, false);
    
    // when
    jippi::IssueTypeFieldParser *jsonParser = new jippi::IssueTypeFieldParser();
    jippi::issue_type *issueTypeInfo = reinterpret_cast<jippi::issue_type *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("http://test.jira.org/rest/api/2/issuetype/7", issueTypeInfo->self);
    
    delete jsonParser;
}

TEST_F(IssueTypeParserTest, ShouldContainValidId) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_TYPE_JSON, root, false);
    
    // when
    jippi::IssueTypeFieldParser *jsonParser = new jippi::IssueTypeFieldParser();
    jippi::issue_type *issueTypeInfo = reinterpret_cast<jippi::issue_type *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("TEST-ID", issueTypeInfo->id);
    
    delete jsonParser;
}

TEST_F(IssueTypeParserTest, ShouldKnowsIfIsSubtask) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_TYPE_JSON, root, false);
    
    // when
    jippi::IssueTypeFieldParser *jsonParser = new jippi::IssueTypeFieldParser();
    jippi::issue_type *issueTypeInfo = reinterpret_cast<jippi::issue_type *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ(false, issueTypeInfo->subtask);
    
    delete jsonParser;
}


TEST_F(IssueTypeParserTest, ShouldContainValidDescription) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_TYPE_JSON, root, false);
    
    // when
    jippi::IssueTypeFieldParser *jsonParser = new jippi::IssueTypeFieldParser();
    jippi::issue_type *issueTypeInfo = reinterpret_cast<jippi::issue_type *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("TEST-DESCRIPTION", issueTypeInfo->description);
    
    delete jsonParser;
}


TEST_F(IssueTypeParserTest, ShouldContainValidIconUrl) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_TYPE_JSON, root, false);
    
    // when
    jippi::IssueTypeFieldParser *jsonParser = new jippi::IssueTypeFieldParser();
    jippi::issue_type *issueTypeInfo = reinterpret_cast<jippi::issue_type *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("http://test.jira.org/images/icons/issuetypes/story.png", issueTypeInfo->iconUrl);
    
    delete jsonParser;
}


TEST_F(IssueTypeParserTest, ShouldContainValidName) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_TYPE_JSON, root, false);
    
    // when
    jippi::IssueTypeFieldParser *jsonParser = new jippi::IssueTypeFieldParser();
    jippi::issue_type *issueTypeInfo = reinterpret_cast<jippi::issue_type *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("TEST-NAME", issueTypeInfo->name);
    
    delete jsonParser;
}
