#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

using namespace boost::spirit;

int main() {
  std::string s;
  std::getline(std::cin, s);
  auto it = s.begin();

  bool match = qi::phrase_parse(it, s.end(), ascii::digit >> ascii::digit, ascii::space);
  // qi::lexeme[ascii::digit >> ascii::digit]
  // Use the above line to check if the two digits are not having any space in them.
  std::cout<< std::boolalpha << match<< "\n";

  if(it != s.end()){
    std::cout<<std::string{it, s.end()}<<"\n";
  }
  return 0;
}
