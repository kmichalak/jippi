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
#include "json/progress.hpp"
#include "test/include/json/progressparsertest.hpp"

void ProgressParserTest::SetUp()
{

}

void ProgressParserTest::TearDown()
{

}

TEST_F(ProgressParserTest, ContainsValidProgressInfo) 
{
    jippi::ProgressFieldParser *jsonParser = new jippi::ProgressFieldParser();
    std::string jsonDocument = PROGRSS_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
     jippi::progress *progresstInfo = reinterpret_cast<jippi::progress *>(jsonParser->parse(root));
    
    // then
     EXPECT_EQ(0, progresstInfo->progress);
    
    // cleanup
    delete jsonParser;
    delete progresstInfo ;   
}


TEST_F(ProgressParserTest, ContainsValidTotalInfo) 
{
    jippi::ProgressFieldParser *jsonParser = new jippi::ProgressFieldParser();
    std::string jsonDocument = PROGRSS_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
     jippi::progress *progresstInfo = reinterpret_cast<jippi::progress *>(jsonParser->parse(root));
    
    // then
     EXPECT_EQ(14400, progresstInfo->total);
    
    // cleanup
    delete jsonParser;
    delete progresstInfo ;   
}


TEST_F(ProgressParserTest, ContainsValidPercentInfo) 
{
    jippi::ProgressFieldParser *jsonParser = new jippi::ProgressFieldParser();
    std::string jsonDocument = PROGRSS_JSON;
    
    Json::Value root;
    Json::Reader jsonReader;
    jsonReader.parse(jsonDocument, root, false);
    
    // when
     jippi::progress *progresstInfo = reinterpret_cast<jippi::progress *>(jsonParser->parse(root));
    
    // then
     EXPECT_EQ(0, progresstInfo->percent);
    
    // cleanup
    delete jsonParser;
    delete progresstInfo ;   
}
