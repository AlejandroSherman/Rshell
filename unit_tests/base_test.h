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

TEST(BaseTestSet, base_end_spaces_parse)
{
  Base *input = new Command();
  string userinput = "  echo hi how ya doing  ";
  vector <string> tokens = (input->parsing(userinput));
  ASSERT_EQ(tokens.size(), 5);
  cout << "echo hi how ya doing" << endl;
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

TEST(BaseTestSet, base_Paren1_parse)
{
    Base* input = new Command();
    string userinput = "echo a && (echo b || echo c)";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 10);
    cout << "echo a && ( echo b || echo c )" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}

TEST(BaseTestSet, base_Paren2_parse)
{
    Base* input = new Command();
    string userinput = "echo a && (echo b || (echo c && echo d))";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 15);
    cout << "echo a && ( echo b || ( echo c && echo d ) )" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}

TEST(BaseTestSet, base_Paren3_parse)
{
    Base* input = new Command();
    string userinput = "()()echo (a) && (echo b (||) (echo c && echo d))";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 23);
    cout << "( ) ( ) echo ( a ) && ( echo b ( || ) ( echo c && echo d ) )" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}

TEST(BaseTestSet, base_Paren4_parse)
{
    Base* input = new Command();
    string userinput = "((ls -a)";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 5);
    cout << "( ( ls -a )" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}

TEST(BaseTestSet, base_Paren5_parse)
{
    Base* input = new Command();
    string userinput = "((ls -a)&&(echo bye))";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 11);
    cout << "( ( ls -a ) && ( echo bye ) )" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}

TEST(BaseTestSet, base_SqBracket1_parse)
{
    Base* input = new Command();
    string userinput = "[ -e test/file/path ]";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 4);
    cout << "[ -e test/file/path ]" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}

TEST(BaseTestSet, base_SqBracket2_parse)
{
    Base* input = new Command();
    string userinput = "[-e test/file/path]";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 2);
    cout << "[-e test/file/path]" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}

TEST(BaseTestSet, base_SqBracket3_parse)
{
    Base* input = new Command();
    string userinput = "[ -e test/file/path ] && [ -d test/file/valid ]";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 9);
    cout << "[ -e test/file/path ] && [ -d test/file/valid ]" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}

TEST(BaseTestSet, base_SqBracket4_parse)
{
    Base* input = new Command();
    string userinput = " [ -e test/file/path ] || (test -e path || [ -f localpath ])";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 15);
    cout << "[ -e test/file/path ] || ( test -e path || [ -f localpath ] )" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}

TEST(BaseTestSet, base_SqBracket5_parse)
{
    Base* input = new Command();
    string userinput = " [ ]";
    vector <string> tokens = (input->parsing(userinput));
    ASSERT_EQ(tokens.size(), 2);
    cout << "[ ]" << endl;
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i) << " ";
    }
}
#endif // !_BASE_TEST_H_
