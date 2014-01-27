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

#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <gtest/gtest.h>

void EXPECT_SEME_ORDER(std::vector<std::string> vec, std::string *strings)
{
	int counter = 0;
	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it) {
		EXPECT_EQ(0, strings[counter++].compare(*it));
	}
		
}

#endif // ASSERT_H