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
#include "jsonparser/votesparser.hpp"
#include "test/include/jsonparser/votesparsertest.hpp"

void VotesParserTest::SetUp()
{

}

void VotesParserTest::TearDown()
{

}

TEST_F(VotesParserTest, ShouldContainValidSelfInfo) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(VOTE_JSON, root, false);
    
    // when
    jippi::VotesParser *jsonParser = new jippi::VotesParser();
    jippi::votes *votesInfo = reinterpret_cast<jippi::votes *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ("http://test.jira.org/rest/api/2/issue/TEST-1/votes", votesInfo->self);
    
    delete jsonParser;
}

TEST_F(VotesParserTest, ShouldContainValidVotesCount) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(VOTE_JSON, root, false);
    
    // when
    jippi::VotesParser *jsonParser = new jippi::VotesParser();
    jippi::votes *votesInfo = reinterpret_cast<jippi::votes *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ(12, votesInfo->votes);
    
    delete jsonParser;
}

TEST_F(VotesParserTest, ShouldContainKnowsAboutVotes) 
{
    // given
    Json::Reader jsonReader;
    Json::Value root;
    jsonReader.parse(VOTE_JSON, root, false);
    
    // when
    jippi::VotesParser *jsonParser = new jippi::VotesParser();
    jippi::votes *votesInfo = reinterpret_cast<jippi::votes *>(jsonParser->parse(root));
    
    // then
    
    EXPECT_EQ(true, votesInfo->hasVoted);
    
    delete jsonParser;
}
