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
#include "include/restclienttest.hpp"
#include "../../../src/rest/client/include/restclient.hpp"

void RestClientTest::SetUp() 
{
	url = "http://echo.jsontest.com/value/get";	
	client = new RestClient;
}


TEST_F(RestClientTest, GetReturns200WhenOk)
{
	// when
	rest_response response = client->get(url);
	// then	
	EXPECT_EQ(200, response.code);
}


TEST_F(RestClientTest, GetReturnsValidResponseBody)
{
	// when
	rest_response response = client->get(url);
	// then
	EXPECT_EQ("{\"value\": \"get\"}\n", response.body);
}

TEST_F(RestClientTest, ShouldReturnValidResponseCodeWhenFails)
{
	rest_response response = client->get("http://nonexisting.org");
	EXPECT_EQ(-1, response.code);
}

