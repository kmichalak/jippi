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
#include <jsoncpp/json/reader.h>
#include "issue.hpp"
#include "test/issueparsertest.hpp"

void IssueParserTest::SetUp()
{

}

void IssueParserTest::TearDown()
{

}

TEST_F(IssueParserTest, ShouldContainValidIssueId) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_JSON, root, false);
    
    // when
    
    jippi::IssueParser *jsonParser = new jippi::IssueParser();
    jsonParser->initialize();
    jippi::issue issueInfo = jsonParser->parse(root);
    
    // then
    
    EXPECT_EQ("TEST_ID", issueInfo.id);
    
    delete jsonParser;
}

TEST_F(IssueParserTest, ShouldContainValidSelfInfo) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_JSON, root, false);
    
    // when
    
    jippi::IssueParser *jsonParser = new jippi::IssueParser();
    jsonParser->initialize();
    jippi::issue issueInfo = jsonParser->parse(root);
    
    // then
    
    EXPECT_EQ("http://test.jira.org", issueInfo.self);
    
    delete jsonParser;
}

TEST_F(IssueParserTest, ShouldContainValidIssueKey) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_JSON, root, false);
    
    // when
    
    jippi::IssueParser *jsonParser = new jippi::IssueParser();
    jsonParser->initialize();
    jippi::issue issueInfo = jsonParser->parse(root);
    
    // then
    
    EXPECT_EQ("TEST-1", issueInfo.key);
    
    delete jsonParser;
}

TEST_F(IssueParserTest, ShouldContainAllKnownIssueFields) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(ISSUE_JSON, root, false);
    
    // when
    
    jippi::IssueParser *jsonParser = new jippi::IssueParser();
    jsonParser->initialize();
    jippi::issue issueInfo = jsonParser->parse(root);
    
    // then
    
    EXPECT_EQ(2, issueInfo.fieldsCollection.size());
    
    delete jsonParser;
}
