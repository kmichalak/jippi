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
#include "jsonparser/reporter.hpp"
#include "test/include/jsonparser/reporterparsertest.hpp"

TEST_F(ReporterParserTest, ReporterContainsValidSelfUrl)
{
    // given
    jippi::ReporterFieldParser *jsonParser = new jippi::ReporterFieldParser();
    std::string jsonDocument = REPORTER_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
     jippi::field *reporterInfo = jsonParser->parse(root);
    
    // then
     EXPECT_EQ("http://test.jira.org/rest/api/2/user?username=Test.Reporter", reporterInfo->self);
    
    // cleanup
    delete jsonParser;
    delete reporterInfo;
}

TEST_F(ReporterParserTest, ReporterContainsValidName)
{
    // given
    jippi::ReporterFieldParser *jsonParser = new jippi::ReporterFieldParser();
    std::string jsonDocument = REPORTER_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
     jippi::field *reporterInfo = jsonParser->parse(root);
    
    // then
     EXPECT_EQ("Test.Reporter", reporterInfo->name);
    
    // cleanup
    delete jsonParser;
    delete reporterInfo;
}


TEST_F(ReporterParserTest, ReporterContainsValidEmailAddress)
{
    // given
    jippi::ReporterFieldParser *jsonParser = new jippi::ReporterFieldParser();
    std::string jsonDocument = REPORTER_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
      jippi::reporter *reporterInfo = reinterpret_cast<jippi::reporter *>(jsonParser->parse(root));
    
    // then
     EXPECT_EQ("test.reporter@test.org", reporterInfo->emailAddress);
    
    // cleanup
    delete jsonParser;
    delete reporterInfo;
    
}

TEST_F(ReporterParserTest, ReporterContainsValidDisplayName)
{
    // given
    jippi::ReporterFieldParser *jsonParser = new jippi::ReporterFieldParser();
    std::string jsonDocument = REPORTER_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
    jippi::reporter *reporterInfo = reinterpret_cast<jippi::reporter *>(jsonParser->parse(root));
    
    // then
    EXPECT_EQ("Reporter, Test", reporterInfo->displayName);
    
    // cleanup
    delete jsonParser;
    delete reporterInfo;
}


TEST_F(ReporterParserTest, ReporterContainsValidActiveFlag)
{
    // given
    jippi::ReporterFieldParser *jsonParser = new jippi::ReporterFieldParser();
    std::string jsonDocument = REPORTER_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
    jippi::reporter *reporterInfo = reinterpret_cast<jippi::reporter *>(jsonParser->parse(root));
    
    // then
    EXPECT_EQ(true, reporterInfo->active);
    
    // cleanup
    delete jsonParser;
    delete reporterInfo;    
}


TEST_F(ReporterParserTest, ReporterContainsFullSetOfAvatars)
{
    // given
    jippi::ReporterFieldParser *jsonParser = new jippi::ReporterFieldParser();
    std::string jsonDocument = REPORTER_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
    jippi::reporter *reporterInfo = reinterpret_cast<jippi::reporter *>(jsonParser->parse(root));
    
    // then
    EXPECT_EQ(
        "http://test.jira.org/secure/useravatar?size=xsmall&ownerId="
        "test.reporter&avatarId=12726", 
        reporterInfo->avatarUrls.size16x16);
    
    EXPECT_EQ(
        "http://test.jira.org/secure/useravatar?size=small&ownerId="
        "test.reporter&avatarId=12726", 
        reporterInfo->avatarUrls.size24x24);
    
    EXPECT_EQ(
        "http://test.jira.org/secure/useravatar?size=medium&ownerId="
        "test.reporter&avatarId=12726", 
        reporterInfo->avatarUrls.size32x32);
    
    EXPECT_EQ(
        "http://test.jira.org/secure/useravatar?ownerId="
        "test.reporter&avatarId=12726", 
        reporterInfo->avatarUrls.size48x48);
    
    // cleanup
    delete jsonParser;
    delete reporterInfo;    
}
