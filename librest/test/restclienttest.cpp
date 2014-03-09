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
#include <curl/curl.h>
#include "librest/test/restclienttest.hpp"
#include "librest/src/restclient.hpp"

void RestClientTest::SetUp() 
{
    get_url = "http://echo.jsontest.com/value/get";
    put_url = "http://httpbin.org/put";
    post_url = "http://httpbin.org/post";
    content_type = "application/json";
    client = new jippi::RestClient;
}

//---------------------------------------------
// GET
//---------------------------------------------

TEST_F(RestClientTest, ResponseShouldContain200CodeWhenGetSucceed)
{
    // when
    jippi::rest_response response = client->doHttpGet(get_url);
    // then    
    EXPECT_EQ(200, response.code);
}


TEST_F(RestClientTest, ResponseShouldContainValidResponseBodyWhenGetSucceed)
{
    // when
    jippi::rest_response response = client->doHttpGet(get_url);
    // then
    EXPECT_EQ("{\"value\": \"get\"}\n", response.body);
}

TEST_F(RestClientTest, ResponseShouldContainValidResponseCodeWhenGetFails)
{
    // when
    jippi::rest_response response = client->doHttpGet("http://nonexisting.org");
    // then
    EXPECT_EQ(CURLE_COULDNT_RESOLVE_HOST, response.code);
}


//---------------------------------------------
// PUT
//---------------------------------------------

TEST_F(RestClientTest, ResponseShouldContain200CodeWhenPutSucceed)
{
    // given
    std::string data = "testdata";
    // when
    jippi::rest_response response = client->doHttpPut(put_url, content_type, data);
    // then
    EXPECT_EQ(200, response.code);
}

TEST_F(RestClientTest, ResponseShouldContainValidResponseBodyWhenPutSucceed)
{
    // given
    std::string data = "testdata";
    // when
    jippi::rest_response response = client->doHttpPut(put_url, content_type, data);
    size_t data_content_position = response.body.find(data);
    // then
     ASSERT_TRUE(data_content_position != std::string::npos);
}

TEST_F(RestClientTest, ResponseShouldContainValidCodeWhenPutFails)
{
    // given
    std::string data = "testdata";
    // when
    jippi::rest_response response = client->doHttpPut("http://nonexisting.org", content_type, data);
    // then
    EXPECT_EQ(CURLE_COULDNT_RESOLVE_HOST, response.code);
}

//---------------------------------------------
// POST
//---------------------------------------------

TEST_F(RestClientTest, ResponseShouldContainValidResponseCodeWhenPostSucceed) 
{
    // given
    std::string data = "testdata";
    // when
    jippi::rest_response response = client->doHttpPost(post_url, content_type, data);
    // then
    EXPECT_EQ(200, response.code);
}

TEST_F(RestClientTest, ResponseShouldContainValidResponseBodyWhenPostSucceed) 
{
    // given
    std::string data = "testdata";
    // when
    jippi::rest_response response = client->doHttpPost(post_url, content_type, data);
    size_t data_content_position = response.body.find(data);
    // then
    ASSERT_TRUE(data_content_position != std::string::npos);
}

TEST_F(RestClientTest, ResponseShouldContainValidCodeWhenPostFails)
{
    // given 
    std::string data = "testdata";
    // when
    jippi::rest_response response = client->doHttpPost("http://notexisting.org", content_type, data);
    // then
    EXPECT_EQ(CURLE_COULDNT_RESOLVE_HOST, response.code);
}