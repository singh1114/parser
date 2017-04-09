#include <boost/spirit/include/qi.hpp>
#include <string>
#include <iostream>

using namespace boost::spirit;

int main()
{
  std::string s;
  std::getline(std::cin, s);

  // auto type gives the type to the variable automatically.
  // initialize it to the beginning of the string.
  auto it = s.begin();

  /*
  qi::parse takes three arguments
  first: iterator that is initized to the first variable
  second: condition to be true
  third: the test case. The parser check if the string is in this class
  match = true if the it is in ascii::digit class
  */
  bool match = qi::parse(it, s.end(), ascii::digit);
  // boolalpha converts passed (<< var) to either true or false otherwise it will
  // print 0 or 1.
  std::cout << std::boolalpha << match << '\n';

  // If the final is not reached print the other string.
  if (it != s.end())
    std::cout << std::string{it, s.end()} << '\n';
}
