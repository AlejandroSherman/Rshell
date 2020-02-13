//semi test h
#ifndef _SEMI_TEST_H_
#define _SEMI_TEST_H_
using namespace std;
#include "../header/semi.h"
TEST(SemiTestSet, semi_True_True)
{
	vector <string> vec1, vec2;
	vec1.push_back("ls");
	vec1.push_back("-a");
	vec2.push_back("ls");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	Semi* test = new Semi(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, true);
}

TEST(SemiTestSet, semi_True_False)
{
	vector <string> vec1, vec2;
	vec1.push_back("ls");
	vec1.push_back("-a");
	vec2.push_back("Invalid");
	vec2.push_back("-a");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	Semi* test = new Semi(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, false);
}

TEST(SemiTestSet, semi_False_True)
{
	vector <string> vec1, vec2;
	vec1.push_back("Invalid");
	vec1.push_back("-a");
	vec2.push_back("ls");
	vec2.push_back("-a");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	Semi* test = new Semi(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, true);
}

TEST(SemiTestSet, semi_False_False)
{
	vector <string> vec1, vec2;
	vec1.push_back("Invalid");
	vec1.push_back("-a");
	vec2.push_back("Wrong");
	vec2.push_back("-a");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	Semi* test = new Semi(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, false);
}
#endif // !_OR_TEST_H_
