#ifndef _OUTPUT_TEST_H_
#define _OUTPUT_TEST_H_
using namespace std;
#include "../header/output_a.h"
#include "../header/output_t.h"
#include "../header/and.h"

TEST(OutputTestSet, output_t1)
{
	vector <string> vec1, vec2;
  vec1.push_back("echo");
  vec1.push_back("Hello there");
	vec2.push_back("unit.txt");

	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	Output_T* test = new Output_T(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, true);
}

TEST(OutputTestSet, output_a1)
{
	vector <string> vec1, vec2;
  vec1.push_back("echo");
  vec1.push_back("Hello there");
	vec2.push_back("unit.txt");

	Command* cmd1 = new Command(vec1.at(0), vec1);
	Command* cmd2 = new Command(vec2.at(0), vec2);
	Output_A* test = new Output_A(cmd1, cmd2);
	bool result = test->execute();
	EXPECT_EQ(result, true);
}

TEST(OutputTestSet, both_outputs)
{
	vector <string> vec1, vec2;
  vec1.push_back("echo");
  vec1.push_back("T here");
	vec2.push_back("unit2.txt");

	Command* cmd3 = new Command(vec1.at(0), vec1);
	Command* cmd4 = new Command(vec2.at(0), vec2);
	Output_T* test = new Output_T(cmd3, cmd4);
	bool result = test->execute();

  vector <string> vec3, vec4;
  vec3.push_back("echo");
  vec3.push_back("A here");
	vec4.push_back("unit2.txt");

	Command* cmd1 = new Command(vec3.at(0), vec3);
	Command* cmd2 = new Command(vec4.at(0), vec4);
	Output_A* test2 = new Output_A(cmd1, cmd2);
	bool result2 = test2->execute();
	EXPECT_EQ(result, true);
  EXPECT_EQ(result2, true);

  vector <string> vec5, vec6;
  vec5.push_back("rm");
  vec5.push_back("unit.txt");
  vec6.push_back("rm");
  vec6.push_back("unit2.txt");
  Command* cmd5 = new Command(vec5.at(0), vec5);
  Command* cmd6 = new Command(vec6.at(0), vec6);
  And* cleaner = new And(cmd5, cmd6);
  bool cleaner_result = cleaner->execute();
  EXPECT_EQ(cleaner_result, true);
}

#endif
