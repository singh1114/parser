#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/config/warning_disable.hpp>

#include <iostream>
#include <string>

namespace client {
  namespace qi = boost::spirit::qi;
  namespace phoenix = boost::phoenix;
  namespace ascii = boost::spirit::ascii;

  // start the symbols, they might be the terminals

  // : operator is used to inherit or extend the symbols class

  // When an object is created it is assigned with a char and an corresponding unsigned value
  struct hundred_: qi::symbols<char, unsigned>{

    // This is the constructor
    hundred_() {
      add
        ("C"    , 100)
        ("CC"   , 200)
        ("CCC"  , 300)
        ("CD"   , 400)
        ("D"    , 500)
        ("DC"   , 600)
        ("DCC"  , 700)
        ("DCCC" , 800)
        ("CM"   , 900)
      ;
    }
  } hundred;

  struct tens_: qi::symbols<char, unsigned>{
    tens_() {
      add
        ("X"    , 10)
        ("XX"   , 20)
        ("XXX"  , 30)
        ("XL"   , 40)
        ("L"    , 50)
        ("LX"   , 60)
        ("LXX"  , 70)
        ("LXXX" , 80)
        ("XC"   , 90)
      ;
    }
  }tens;


  struct ones_ : qi::symbols<char, unsigned> {
    ones_() {
      add
        ("I"    , 1)
        ("II"   , 2)
        ("III"  , 3)
        ("IV"   , 4)
        ("V"    , 5)
        ("VI"   , 6)
        ("VII"  , 7)
        ("VIII" , 8)
        ("IX"   , 9)
      ;
    }
  } ones;
  // End the symbols

  template <typename Iterator>
  struct roman: qi::grammar<Iterator, unsigned()>{
    // There is something happening here which I was not able to understand.
    // check it out.
    roman(): roman::base_type(start) {
      using ascii::char_;

      // Start works even before the string is started processing so we can intialize some values

      start = qi::eps    [qi::_val = 0] >>
        (
          // If the literal is M add 1000 to the returning variable
          +qi::lit('M')    [qi::_val += 1000]
          || hundred       [qi::_val += qi::_1]
          || tens          [qi::_val += qi::_1]
          || ones          [qi::_val += qi::_1]
        )
      ;
    }

    qi::rule<Iterator, unsigned()> start;
  };

  // typedef std::string::const_iterator iterator_type;
  // typedef roman<iterator_type> roman;
  // unsigned result;
  // roman roman_parser;
  // template <typename Iterator>
  // unsigned int parseRoman(Iterator start, Iterator end, roman_parser, result) {
  //   qi::phrase_parse(start, end, roman_parser, result);
  //   if(start != end) {
  //     std::cout<<"We were not able to parse the string";
  //     return 0;
  //   }
  //   return result;
  // }
}

int main() {
  namespace qi = boost::spirit::qi;
	std::string s;
	std::getline(std::cin, s);
	auto start = s.begin();
	typedef std::string::const_iterator iterator_type;
	typedef client::roman<iterator_type> roman;
  roman roman_parser;
	// create the object of roman type created in last line

	unsigned result;
  std::string::const_iterator iter = s.begin();
  std::string::const_iterator end = s.end();
	if(qi::parse(iter, end, roman_parser, result)){

	   std::cout<<"The calculated value is: "<<result;
  }
	return 0;
}
