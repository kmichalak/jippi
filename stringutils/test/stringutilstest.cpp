/*
 * Copyright 2013 Kamil Michalak <kmichalak8@gmail.com>
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

#include <gtest/gtest.h>
#include <vector>
#include "stringutilstest.hpp"
#include "test/inc/assert.hpp"
#include "stringutils/stringutils.hpp"

//------------------------------------------------------------------------------
// Trim
//------------------------------------------------------------------------------

TEST(StringUtilsTest, TrimCutsLeadingSpaces)
{
    // given 
    const std::string & test_string = std::string(" test string");    
    // when
    std::string result = jippi::StringUtils::trim(test_string);    
    // then
    EXPECT_EQ("test string", result);
}


TEST(StringUtilsTest, TrimCutsTrailingSpaces)
{
    // given 
    const std::string & test_string = std::string("test string ");
    // when
    std::string result = jippi::StringUtils::trim(test_string);
    // then
    EXPECT_EQ("test string", result);
}


TEST(StringUtilsTest, TrimCutsLeadingAndTrailingSpaces)
{
    // given 
    const std::string & test_string = std::string(" test string ");
    // when
    std::string result = jippi::StringUtils::trim(test_string);
    // then
    EXPECT_EQ("test string", result);
}


//------------------------------------------------------------------------------
// Is empty
//------------------------------------------------------------------------------

TEST(StringUtilsTest, IsEmptyReturnsTrueWhenStringIsEmpty)
{
    // given 
    const std::string test_string;
    // when
    bool result = jippi::StringUtils::isEmpty(test_string);
    // then
    ASSERT_TRUE(result);
}


//------------------------------------------------------------------------------
// Split
//------------------------------------------------------------------------------

TEST(StringUtilsTest, IsEmptyReturnsFalseWhenStringIsNotEmpty)
{
    // given 
    const std::string test_string = std::string("test string");
    // when
    bool result = jippi::StringUtils::isEmpty(test_string);
    // then
    ASSERT_FALSE(result);
}

TEST(StringUtilsTest, SplitReturnsSingleValueWhenNoDelimiter)
{
    //given 
    const std::string &test_string = std::string("teststring");
    const char delim = '.';
    
    // when 
    std::vector<std::string> result = jippi::StringUtils::split(test_string, delim);
    
    // then
    EXPECT_EQ(1, result.size());
}

TEST(StringUtilsTest, SplitReturnsValidNumberOfResults)
{
    //given 
    const std::string &test_string = std::string("test.string.with.dots");
    const char delim = '.';
    std::string strings[4] = {"test", "string", "with", "dots"};
    
    // when 
    std::vector<std::string> result = jippi::StringUtils::split(test_string, delim);
    
    // then
    EXPECT_EQ(4, result.size());
    EXPECT_SEME_ORDER(result, strings);
}
