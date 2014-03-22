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
#include <jsoncpp/json/reader.h>
#include "json/assignee.hpp"
#include "test/include/json/assigneeparsertest.hpp"

TEST_F(AssigneeParserTest, AssgneeContainsValidSelfUrl)
{
    // given
    jippi::AssigneeFieldParser *jsonParser = new jippi::AssigneeFieldParser();
    std::string jsonDocument = ASSIGNEE_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
     jippi::field *assigneeInfo = jsonParser->parse(root);
    
    // then
     EXPECT_EQ("http://test.jira.org/rest/api/2/user?username=test.reporter", assigneeInfo->self);
    
    // cleanup
    delete jsonParser;
    delete assigneeInfo;
}

TEST_F(AssigneeParserTest, AssgneeContainsValidName)
{
    // given
    jippi::AssigneeFieldParser *jsonParser = new jippi::AssigneeFieldParser();
    std::string jsonDocument = ASSIGNEE_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
     jippi::field *assigneeInfo = jsonParser->parse(root);
    
    // then
     EXPECT_EQ("Test.Reporter", assigneeInfo->name);
    
    // cleanup
    delete jsonParser;
    delete assigneeInfo;
}


TEST_F(AssigneeParserTest, AssgneeContainsValidEmailAddress)
{
    // given
    jippi::AssigneeFieldParser *jsonParser = new jippi::AssigneeFieldParser();
    std::string jsonDocument = ASSIGNEE_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
      jippi::assignee *assigneeInfo = reinterpret_cast<jippi::assignee *>(jsonParser->parse(root));
    
    // then
     EXPECT_EQ("test.reporter@test.org", assigneeInfo->emailAddress);
    
    // cleanup
    delete jsonParser;
    delete assigneeInfo;
    
}

TEST_F(AssigneeParserTest, AssgneeContainsValidDisplayName)
{
    // given
    jippi::AssigneeFieldParser *jsonParser = new jippi::AssigneeFieldParser();
    std::string jsonDocument = ASSIGNEE_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
    jippi::assignee *assigneeInfo = reinterpret_cast<jippi::assignee *>(jsonParser->parse(root));
    
    // then
    EXPECT_EQ("Reporter, Test", assigneeInfo->displayName);
    
    // cleanup
    delete jsonParser;
    delete assigneeInfo;
}


TEST_F(AssigneeParserTest, AssgneeContainsValidActiveFlag)
{
    // given
    jippi::AssigneeFieldParser *jsonParser = new jippi::AssigneeFieldParser();
    std::string jsonDocument = ASSIGNEE_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
    jippi::assignee *assigneeInfo = reinterpret_cast<jippi::assignee *>(jsonParser->parse(root));
    
    // then
    EXPECT_EQ(true, assigneeInfo->active);
    
    // cleanup
    delete jsonParser;
    delete assigneeInfo;    
}


TEST_F(AssigneeParserTest, AssgneeContainsFullSetOfAvatars)
{
    // given
    jippi::AssigneeFieldParser *jsonParser = new jippi::AssigneeFieldParser();
    std::string jsonDocument = ASSIGNEE_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
    jippi::assignee *assigneeInfo = reinterpret_cast<jippi::assignee *>(jsonParser->parse(root));
    
    // then
    EXPECT_EQ(
        "http://test.jira.org/secure/useravatar?size=xsmall&ownerId="
        "test.reporter&avatarId=12726", 
        assigneeInfo->avatarUrls.size16x16);
    
    EXPECT_EQ(
        "http://test.jira.org/secure/useravatar?size=small&ownerId="
        "test.reporter&avatarId=12726", 
        assigneeInfo->avatarUrls.size24x24);
    
    EXPECT_EQ(
        "http://test.jira.org/secure/useravatar?size=medium&ownerId="
        "test.reporter&avatarId=12726", 
        assigneeInfo->avatarUrls.size32x32);
    
    EXPECT_EQ(
        "http://test.jira.org/secure/useravatar?ownerId="
        "test.reporter&avatarId=12726", 
        assigneeInfo->avatarUrls.size48x48);
    
    // cleanup
    delete jsonParser;
    delete assigneeInfo;    
}
