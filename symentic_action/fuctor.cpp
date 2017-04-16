#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <string>

namespace client {
  namespace qi = boost::spirit::qi;

  /* fuctor is a member funtion in which the () operator is overloaded
      So that the object can directly be used as a function.
  */
  struct print_int {
    // The operator overloading needs three params
    // First the real parameter also known as the hit parameter
    void operator()(int const& i, qi::unused_type, qi::unused_type) const{
      std::cout<<i<<std::endl;
    }
  };

  template <typename Iterator>
  void parseString(Iterator start, Iterator end) {
    qi::phrase_parse(
      start,
      end,
      '{' >> qi::int_[print_int()] >> '}',
      qi::space
    );
  }
}

int main() {
  using client::parseString;

  std::cout<<"Enter a string of type '{44}'\n";
  std::string s;
  std::getline(std::cin, s);

  parseString(s.begin(), s.end());
  return 0;
}
