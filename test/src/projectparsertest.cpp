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
#include "inc/json/project.hpp"
#include "test/inc/projectparsertest.hpp"

TEST_F(ProjectParserTest, ProjectContainsValidSelfUrl)
{
    // given
    jippi::ProjectFieldParser *jsonParser = new jippi::ProjectFieldParser();
    std::string jsonDocument = PROJECT_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
     jippi::project *projectInfo = reinterpret_cast<jippi::project *>(jsonParser->parse(root));
    
    // then
     EXPECT_EQ("http://test.jira.org/rest/api/2/project/TEST", projectInfo->self);
    
    // cleanup
    delete jsonParser;
    delete projectInfo;
}

TEST_F(ProjectParserTest, ProjectContainsValidKey)
{
    // given
    jippi::ProjectFieldParser *jsonParser = new jippi::ProjectFieldParser();
    std::string jsonDocument = PROJECT_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
     jippi::project *projectInfo = reinterpret_cast<jippi::project *>(jsonParser->parse(root));
    
    // then
     EXPECT_EQ("TEST", projectInfo->key);
    
    // cleanup
    delete jsonParser;
    delete projectInfo;
}


TEST_F(ProjectParserTest, ProjectContainsValidName)
{
    // given
    jippi::ProjectFieldParser *jsonParser = new jippi::ProjectFieldParser();
    std::string jsonDocument = PROJECT_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
      jippi::project *projectInfo = reinterpret_cast<jippi::project *>(jsonParser->parse(root));
    
    // then
     EXPECT_EQ("Test Project", projectInfo->name);
    
    // cleanup
    delete jsonParser;
    delete projectInfo;
}


TEST_F(ProjectParserTest, ProjectContainsFullSetOfAvatars)
{
    // given
    jippi::ProjectFieldParser *jsonParser = new jippi::ProjectFieldParser();
    std::string jsonDocument = PROJECT_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
    jippi::project *projectInfo = reinterpret_cast<jippi::project *>(jsonParser->parse(root));
    
    // then
    EXPECT_EQ(
        "http://test.jira.org/secure/projectavatar?"
        "size=xsmall&pid=12633&avatarId=12734", 
        projectInfo->avatarUrls.size16x16);
    
    EXPECT_EQ(
        "http://test.jira.org/secure/projectavatar?"
        "size=small&pid=12633&avatarId=12734", 
        projectInfo->avatarUrls.size24x24);
    
    EXPECT_EQ(
        "http://test.jira.org/secure/projectavatar?"
        "size=medium&pid=12633&avatarId=12734", 
        projectInfo->avatarUrls.size32x32);
    
    EXPECT_EQ(
        "http://test.jira.org/secure/projectavatar?"
        "pid=12633&avatarId=12734", 
        projectInfo->avatarUrls.size48x48);
    
    // cleanup
    delete jsonParser;
    delete projectInfo;    
}
