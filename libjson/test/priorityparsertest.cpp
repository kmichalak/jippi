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
#include <gtest/gtest.h>
#include <jsoncpp/json/reader.h>
#include "priorityparser.hpp"
#include "test/priorityparsertest.hpp"

void PriorityParserTest::SetUp()
{

}

void PriorityParserTest::TearDown()
{

}


TEST_F(PriorityParserTest, ShouldContainValidSelfUrl)
{
     // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(PRIORITY_JSON, root, false);
    
    // when
    jippi::PriorityParser *jsonParser = new jippi::PriorityParser();
    jippi::priority *priorityInfo = reinterpret_cast<jippi::priority *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("http://test.jira.org/rest/api/2/priority/3", priorityInfo->self);
    
    delete jsonParser;
}


TEST_F(PriorityParserTest, ShouldContainValidId)
{
     // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(PRIORITY_JSON, root, false);
    
    // when
    jippi::PriorityParser *jsonParser = new jippi::PriorityParser();
    jippi::priority *priorityInfo = reinterpret_cast<jippi::priority *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("TEST-ID", priorityInfo->id);
    
    delete jsonParser;
}


TEST_F(PriorityParserTest, ShouldContainValidName)
{
     // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(PRIORITY_JSON, root, false);
    
    // when
    jippi::PriorityParser *jsonParser = new jippi::PriorityParser();
    jippi::priority *priorityInfo = reinterpret_cast<jippi::priority *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("TEST-NAME", priorityInfo->name);
    
    delete jsonParser;
}


TEST_F(PriorityParserTest, ShouldContainValidIconUrl)
{
     // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(PRIORITY_JSON, root, false);
    
    // when
    jippi::PriorityParser *jsonParser = new jippi::PriorityParser();
    jippi::priority *priorityInfo = reinterpret_cast<jippi::priority *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("http://test.jira.org/images/icons/priorities/major.png", priorityInfo->iconUrl);
    
    delete jsonParser;
}