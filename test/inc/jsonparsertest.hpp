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

#ifndef JSONPARSERTEST_H
#define JSONPARSERTEST_H

#include <gtest/gtest.h>


class JsonParserTest : public testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();

protected:
	const std::string SINGLE_ISSUE_JSON = 
		"{\"expand\":\"schema,names\",\"startAt\":0,\"maxResults\":2,"
		"\"total\":49922,\"issues\":[{\"expand\":\"editmeta,renderedFields,"
		"transitions,changelog,operations\",\"id\":\"TEST_ISSUE_ID\",\"self\":"
		"\"http://test.jira.org\",\"key\":\"TEST-1\",\"fields\":"
		"{\"summary\":\"Test summary\",\"reporter\":{\"self\":"
		"\"http://test.jira.org/rest/api/2/user?username=Test.Reporter\","
		"\"name\":\"Test.Reporter\",\"emailAddress\":\"test.reporter@test.org\","
		"\"avatarUrls\":{\"16x16\":\"http://test.jira.org/secure/useravatar?size="
		"xsmall&ownerId=test.reporter&avatarId=12726\",\"24x24\":"
		"\"http://test.jira.org/secure/useravatar?size=small&ownerId="
		"test.reporter&avatarId=12726\",\"32x32\":"
		"\"http://test.jira.org/secure/useravatar?size=medium&ownerId="
		"test.reporter&avatarId=12726\",\"48x48\":"
		"\"http://test.jira.org/secure/useravatar?ownerId=test.reporter&avatarId=12726\"},"
		"\"displayName\":\"Reporter, Test\",\"active\":true},\"assignee\":"
		"{\"self\":\"http://test.jira.org/rest/api/2/user?username=test.reporter\","
		"\"name\":\"Test.Reporter\",\"emailAddress\":\"test.reporter@test.org\","
		"\"avatarUrls\":{\"16x16\":\"http://test.jira.org/secure/useravatar?size="
		"xsmall&ownerId=test.reporter&avatarId=12726\",\"24x24\":"
		"\"http://test.jira.org/secure/useravatar?size=small&ownerId="
		"test.reporter&avatarId=12726\",\"32x32\":"
		"\"http://test.jira.org/secure/useravatar?size=medium&ownerId="
		"test.reporter&avatarId=12726\",\"48x48\":"
		"\"http://test.jira.org/secure/useravatar?ownerId=test.reporter&avatarId=12726\"},"
		"\"displayName\":\"Reporter, Test\",\"active\":true},"
		"\"aggregatetimeestimate\":14400,\"aggregatetimespent\":null}}]}";
};

#endif // JSONPARSERTEST_H
