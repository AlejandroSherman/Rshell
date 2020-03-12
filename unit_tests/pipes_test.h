//and test hpp
#ifndef _PIPES_TEST_H_
#define _PIPES_TEST_H_
using namespace std; 
#include "../header/pipes.h"

TEST(PipesTestSet, pipe1)
{
	vector <string> vec1, vec2; 
	vec1.push_back("cat");
	vec1.push_back("input.txt");
	vec2.push_back("tr");
	vec2.push_back("a-z");
	vec2.push_back("A-Z");
	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	Pipes* test = new Pipes(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, true);
}


#endif 
