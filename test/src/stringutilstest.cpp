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
#include "../inc/stringutilstest.hpp"
#include "../../inc/stringutils.hpp"


TEST(StringUtilsTest, TrimCutsLeadingSpaces)
{
	// given 
	const std::string & test_string = std::string(" test string");	
	// when
	std::string result = StringUtils::trim(test_string);	
	// then
	EXPECT_EQ("test string", result);
}


TEST(StringUtilsTest, TrimCutsTrailingSpaces)
{
	// given 
	const std::string & test_string = std::string("test string ");
	// when
	std::string result = StringUtils::trim(test_string);
	// then
	EXPECT_EQ("test string", result);
}


TEST(StringUtilsTest, TrimCutsLeadingAndTrailingSpaces)
{
	// given 
	const std::string & test_string = std::string(" test string ");
	// when
	std::string result = StringUtils::trim(test_string);
	// then
	EXPECT_EQ("test string", result);
}


TEST(StringUtilsTest, IsEmptyReturnsTrueWhenStringIsEmpty)
{
	// given 
	const std::string test_string;
	// when
	bool result = StringUtils::is_empty(test_string);
	// then
	ASSERT_TRUE(result);
}


TEST(StringUtilsTest, IsEmptyReturnsFalseWhenStringIsNotEmpty)
{
	// given 
	const std::string test_string = std::string("test string");
	// when
	bool result = StringUtils::is_empty(test_string);
	// then
	ASSERT_FALSE(result);
}
