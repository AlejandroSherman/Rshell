//base test h
//semi test h
#ifndef _BASE_TEST_H_
#define _BASE_TEST_H_
using namespace std;
#include "../header/base.h"
#include "../header/command.h"
#include <string>
TEST(BaseTestSet, base_normal_parse)
{
  Base *input = new Command();
  string userinput = "echo hi how ya doing";
  vector <string> tokens = (input->parsing(userinput));
  ASSERT_EQ(tokens.size(), 5);
  cout << userinput << endl;
  for (int i = 0; i < tokens.size(); ++i){
    cout << tokens.at(i) << " ";
  }
}

TEST(BaseTestSet, base_comment_parse)
{
  Base *input = new Command();
  string userinput = "echo hi # how ya doing";
  vector <string> tokens = (input->parsing(userinput));
  ASSERT_EQ(tokens.size(), 2);
  cout << "echo hi" << endl;
  for (int i = 0; i < tokens.size(); ++i){
    cout << tokens.at(i) << " ";
  }
}

TEST(BaseTestSet, base_comment_parse2)
{
  Base *input = new Command();
  string userinput = "#";
  vector <string> tokens = (input->parsing(userinput));
  ASSERT_EQ(tokens.size(), 0);
  }
}

TEST(BaseTestSet, base_semi_parse)
{
  Base *input = new Command();
  string userinput = "echo hi; echo bye";
  vector <string> tokens = (input->parsing(userinput));
  ASSERT_EQ(tokens.size(), 5);
  cout << "echo hi ; echo bye" << endl;
  for (int i = 0; i < tokens.size(); ++i){
    cout << tokens.at(i) << " ";
  }
}

TEST(BaseTestSet, base_and_parse)
{
  Base *input = new Command();
  string userinput = "echo hi && echo bye";
  vector <string> tokens = (input->parsing(userinput));
  ASSERT_EQ(tokens.size(), 5);
  cout << "echo hi && echo bye" << endl;
  for (int i = 0; i < tokens.size(); ++i){
    cout << tokens.at(i) << " ";
  }
}

TEST(BaseTestSet, base_or_parse)
{
  Base *input = new Command();
  string userinput = "echo hi || echo bye";
  vector <string> tokens = (input->parsing(userinput));
  ASSERT_EQ(tokens.size(), 5);
  cout << "echo hi || echo bye" << endl;
  for (int i = 0; i < tokens.size(); ++i){
    cout << tokens.at(i) << " ";
  }
}

TEST(BaseTestSet, base_quotes_parse)
{
  Base *input = new Command();
  string userinput = "echo \"hi && echo bye\" ";
  vector <string> tokens = (input->parsing(userinput));
  ASSERT_EQ(tokens.size(), 2);
  cout << "echo hi && echo bye" << endl;
  for (int i = 0; i < tokens.size(); ++i){
    cout << tokens.at(i) << " ";
  }
}
#endif // !_BASE_TEST_H_
