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

#ifndef VOTEPARSERTEST_H
#define VOTEPARSERTEST_H

#include <gtest/gtest.h>

class VotesParserTest : public testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();
    
    const std::string VOTE_JSON = "{"
          "\"self\": \"http://test.jira.org/rest/api/2/issue/TEST-1/votes\","
          "\"votes\": 12,"
          "\"hasVoted\": true"
        "}";
};

#endif // VOTEPARSERTEST_H
