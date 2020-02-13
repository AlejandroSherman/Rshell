//exit test h
#ifndef _EXIT_TEST_H_
#define _EXIT_TEST_H_
using namespace std;
#include "../header/exit.h"
#include "../header/or.h"
#include "../header/semi.h"
#include "../header/and.h"
TEST(ExitTestSet, exit_command_execute)
{
	vector <string> vec1;
	vec1.push_back("exit");
	Exit* test = new Exit(vec1.at(0));
	int result = test->execute();
	EXPECT_EQ(result, 0);
}

TEST(ExitTestSet, command_or_exit)
{
	vector <string> vec1, vec2;
	vec1.push_back("ls");
	vec1.push_back("-a");
	vec2.push_back("exit");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Exit* cmd2 = new Exit(vec2.at(0));
	Or* test = new Or(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, true);
}

TEST(ExitTestSet, exit_and_command)
{
	vector <string> vec1, vec2;
	vec1.push_back("exit");
	vec2.push_back("ls");
  vec2.push_back("-a");
	Exit* cmd1 = new Exit(vec1.at(0));
  Command* cmd2 = new Command(vec2.at(0), vec2);
	And* test = new And(cmd1, cmd2);
	int result = test->execute();
	EXPECT_EQ(result, 0);
}

TEST(ExitTestSet, exit_semi_command)
{
	vector <string> vec1, vec2;
	vec1.push_back("exit");
	vec2.push_back("ls");
  vec2.push_back("-a");
	Exit* cmd1 = new Exit(vec1.at(0));
  Command* cmd2 = new Command(vec2.at(0), vec2);
	Semi* test = new Semi(cmd1, cmd2);
	int result = test->execute();
	EXPECT_EQ(result, 0);
}
#endif // !_OR_TEST_H_
