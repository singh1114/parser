#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/config/warning_disable.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <string>

namespace client {
	namespace qi = boost::spirit::qi;
	namespace phoenix = boost::phoenix;
	namespace ascii = boost::spirit::ascii;

	// Its time to create the grammer
	/*
		grammar description :
			main expression can either be surrounded by braces or they might not be.
			Then another variable will keep track of addition and subtraction operation
			Another variable will keep track of the multiply and divide ops.
			We have to keep in mind the difference between the unary and binary operators as we are using the unsigned ints.

	*/
	template <typename Iterator>
	struct calculatortry: qi::grammar<Iterator, int(), ascii::space_type> {
		// In base_type pass the production rule with which you want to start
		// It is also known as start symbol
		calculatortry(): calculatortry::base_type(mainExpression) {
			qi::_val_type _val;
      qi::_1_type _1;
      qi::uint_type uint_;
			// Now write the various grammer rules
			/*
			mainExpression = mulanddiv + mulanddiv
			|| mainExpression = mulanddiv - mulanddiv
			*/
			mainExpression =
				mulanddiv                  [_val = _1]
				>> *( ('+' >> mulanddiv    [_val += _1])
						| ('-' >> mulanddiv [_val -= _1])
				);

			/*
			mulanddiv = unary * unary
			|| mulanddiv = unary / unary
			*/
			mulanddiv =
				unary                      [_val = _1]
				>> *( ('*' >> unary        [_val *= _1])
						| ('/' >> unary        [_val /= _1])
				);

			/*
			unary = unsignedInt
			|| unary = (mainExpression)
			|| unary = -unary
			|| unary = +unary
			*/

			unary =
				uint_                  [_val = _1]
				| '(' >> mainExpression    [_val = _1] >> ')'
				| ('-' >> unary            [_val = - _1])
				| ('+' >> unary            [_val = _1])
				;
		}
		qi::rule<Iterator, int(), ascii::space_type> mainExpression, mulanddiv, unary;
	};
}

int main() {
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	std::cout<< "Please pass in an expression\n";

	typedef std::string::const_iterator iterator_type;
	typedef client::calculatortry<iterator_type> calculatortry;

	// Create an instanse of struct calculatortry
	calculatortry calculator;
	boost::spirit::ascii::space_type space;

	std::string s;
	std::getline(std::cin, s);

	int result;
	std::string::const_iterator start = s.begin();
	std::string::const_iterator end = s.end();

	if(qi::phrase_parse(start, end, calculator, space, result)){
		std::cout<<"The calculated result is: "<<result;
	}
	return 0;
}
