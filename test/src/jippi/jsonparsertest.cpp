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

#include "jippi/jsonparser.hpp"
#include "test/include/jsonparsertest.hpp"

void JsonParserTest::SetUp() {}

void JsonParserTest::TearDown() {}


TEST_F(JsonParserTest, ShouldReturnValidIssuesCollection) 
{
    // given
    jippi::JsonParser *jsonParser = new jippi::JsonParser();
    std::string jsonDocument = SINGLE_ISSUE_JSON;
    
    // when
    jippi::issues issuesCollection = jsonParser->parseIssues(jsonDocument);
    
    // then
    EXPECT_EQ(1, issuesCollection.size());
    
    // cleanup
    delete jsonParser;
}

TEST_F(JsonParserTest, IssueShouldContainValidId) 
{
    // given
    jippi::JsonParser *jsonParser = new jippi::JsonParser();
    std::string jsonDocument = SINGLE_ISSUE_JSON;
    
    // when
    jippi::issues issuesCollection = jsonParser->parseIssues(jsonDocument);
    jippi::issue issueInfo = *issuesCollection.begin();
    
    // then
    EXPECT_EQ("TEST_ISSUE_ID", issueInfo.id);
    
    // cleanup
    delete jsonParser;
}

TEST_F(JsonParserTest, IssueShouldContainValidKey) 
{
    // given
    jippi::JsonParser *jsonParser = new jippi::JsonParser();
    std::string jsonDocument = SINGLE_ISSUE_JSON;
    
    // when
    jippi::issues issuesCollection = jsonParser->parseIssues(jsonDocument);
    jippi::issue issueInfo = *issuesCollection.begin();
    
    // then
    EXPECT_EQ("TEST-1", issueInfo.key);
    
    // cleanup
    delete jsonParser;
}


TEST_F(JsonParserTest, IssueContainsFields)
{
    // given
    jippi::JsonParser *jsonParser = new jippi::JsonParser();
    std::string jsonDocument = SINGLE_ISSUE_JSON;
    
    // when
    jippi::issues issuesCollection = jsonParser->parseIssues(jsonDocument);
    jippi::issue issueInfo = *issuesCollection.begin();
    
    // then
    EXPECT_EQ(2, issueInfo.fieldsCollection.size());
    
    // cleanup
    delete jsonParser;
}
