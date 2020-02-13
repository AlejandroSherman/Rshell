//and test hpp
#ifndef _AND_TEST_H_
#define _AND_TEST_H_
using namespace std; 
#include "../header/and.h"
TEST(AndTestSet, and_True_True)
{
	vector <string> vec1, vec2; 
	vec1.push_back("ls");
	vec1.push_back("-a");
	vec2.push_back("ls");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	And* test = new And(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, true);
}

TEST(AndTestSet, and_True_False)
{
	vector <string> vec1, vec2;
	vec1.push_back("ls");
	vec1.push_back("-a");
	vec2.push_back("Invalid");
	vec2.push_back("-a");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	And* test = new And(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, false);
}

TEST(AndTestSet, and_False_True)
{
	vector <string> vec1, vec2;
	vec1.push_back("Invalid");
	vec1.push_back("-a");
	vec2.push_back("ls");
	vec2.push_back("-a");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	And* test = new And(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, false);
}

TEST(AndTestSet, and_False_False)
{
	vector <string> vec1, vec2;
	vec1.push_back("Invalid");
	vec1.push_back("-a");
	vec2.push_back("Wrong");
	vec2.push_back("-a");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	And* test = new And(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, false);
}
#endif // !_AND_TEST_H_
