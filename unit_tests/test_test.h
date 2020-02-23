//test unit test file
#include "../header/test.h"
#include <vector>
using namespace std; 

#ifndef _TEST_TEST_H_
#define _TEST_TEST_H_
TEST(Test_test_set, test_test_1)
{
	string cmd = "test"; 
	vector<string> arg;
	Command* test1 = new Test(cmd, arg); 
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_2)
{
	string cmd = "[";
	vector<string> arg;
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_3)
{
	string cmd = "test";
	vector<string> arg;
	arg.push_back("-e");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_4)
{
	string cmd = "test";
	vector<string> arg;
	arg.push_back("-d");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_5)
{
	string cmd = "test";
	vector<string> arg;
	arg.push_back("-f");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_6)
{
	string cmd = "test";
	vector<string> arg;
	arg.push_back("wrongflag");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_7)
{
	string cmd = "[";
	vector<string> arg;
	arg.push_back("-e");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_8)
{
	string cmd = "[";
	vector<string> arg;
	arg.push_back("-d");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_9)
{
	string cmd = "[";
	vector<string> arg;
	arg.push_back("f");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_10)
{
	string cmd = "test";
	vector<string> arg;
	arg.push_back("-e");
	arg.push_back("images");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), true);
}

TEST(Test_test_set, test_test_11)
{
	string cmd = "test";
	vector<string> arg;
	arg.push_back("-d");
	arg.push_back("images");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), true);
}

TEST(Test_test_set, test_test_12)
{
	string cmd = "test";
	vector<string> arg;
	arg.push_back("-f");
	arg.push_back("images");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_13)
{
	string cmd = "[";
	vector<string> arg;
	arg.push_back("-e");
	arg.push_back("]");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_14)
{
	string cmd = "[";
	vector<string> arg;
	arg.push_back("-e");
	arg.push_back("images");
	arg.push_back("]");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), true);
}

TEST(Test_test_set, test_test_15)
{
	string cmd = "[";
	vector<string> arg;
	arg.push_back("-d");
	arg.push_back("images");
	arg.push_back("]");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), true);
}

TEST(Test_test_set, test_test_16)
{
	string cmd = "[";
	vector<string> arg;
	arg.push_back("-f");
	arg.push_back("images");
	arg.push_back("]");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), false);
}

TEST(Test_test_set, test_test_17)
{
	string cmd = "[";
	vector<string> arg;
	arg.push_back("../assignment-empty_string/");
	arg.push_back("]");
	Command* test1 = new Test(cmd, arg);
	EXPECT_EQ(test1->execute(), true);
}
#endif // _TEST_TEST_H_
