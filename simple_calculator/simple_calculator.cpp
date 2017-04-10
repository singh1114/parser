#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

using namespace boost::spirit;

int main() {
  std::string s;
  // get a line of string and store it in the variable s
  std::getline(std::cin, s);
  // Intialize the auto type variable to the start of the string.
  auto it = s.begin();

  double firstVar;
  qi::phrase_parse(it, s.end(), qi::double_, ascii::space, firstVar);

  char signOperator;
  qi::phrase_parse(it, s.end(), qi::byte_, ascii::space, signOperator);

  double secondVar;
  qi::phrase_parse(it, s.end(), qi::double_, ascii::space, secondVar);

  double result;
  if(signOperator == '+'){
    result = firstVar + secondVar;
  }
  else if(signOperator == '-'){
    result = firstVar - secondVar;
  }
  else if(signOperator == '*') {
    result = firstVar * secondVar;
  }
  else if(signOperator == '/') {
    result = firstVar/secondVar;
  }
  else{
    std::cout<<"The string is not valid"<<"\n";
  }

  std::cout<<result<<"\n";
  return 0;
}
