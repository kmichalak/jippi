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

#include "test/inc/querytest.hpp"
#include "inc/query.hpp"
#include "test/inc/assert.hpp"

void QueryTest::SetUp()
{

}


void QueryTest::TearDown()
{

}

TEST_F(QueryTest, QueryShouldDieWhenTargetURLIsEmpty)
{
	// expected
	ASSERT_DEATH(jippi::Query(""), "");
}

TEST_F(QueryTest, WithProjectSetsProjectInJsonStructure)
{
	// given
	std::string projectName = "MyTestProjectToSet";
	jippi::Query *query = new jippi::Query("http:://mock.url.org");
	// when
	query->withProject(projectName);
	std::string jsonPayload = query->getJsonPayload();
	// then
	EXPECT_STR_CONTAINS(jsonPayload, "\"jql\" : \"project = " + projectName+"\"");
}

TEST_F(QueryTest, WithAssigneeSetsAssigneeInJsonStructure)
{
	// when
	std::string assignee = "MyMockAssignee";
	jippi::Query *query = new jippi::Query("http://mock.url.org");
	// when
	query->withAssignee(assignee);
	std::string jsonPayload = query->getJsonPayload();
	// then;
	EXPECT_STR_CONTAINS(jsonPayload, "\"assignee\" : \""+ assignee+"\"");
}

