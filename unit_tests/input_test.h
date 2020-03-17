#ifndef _INPUT_TEST_H_
#define _INPUT_TEST_H_
using namespace std;
#include "../header/input.h"

TEST(InputTestSet, input1)
{
	vector <string> vec1, vec2;
  vec1.push_back("tr");
  vec1.push_back("a-z");
  vec1.push_back("A-Z");
	vec2.push_back("names.txt");

	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	Input* test = new Input(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, true);
}

TEST(InputTestSet, input2)
{
  vector <string> vec1, vec2;
  vec1.push_back("wc");
	vec2.push_back("names.txt");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	Input* test = new Input(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, true);
}


#endif
