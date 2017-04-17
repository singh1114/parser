#include <iostream>
#include <string>
#include <complex>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_core.hpp>

namespace client {
	namespace qi = boost::spirit::qi;
	namespace phoenix = boost::phoenix;

	template <typename Iterator>
	// complex creates a complex number of type double having two paired values
	// first value as the real and the next is the complex part.
	bool parseComplex(Iterator start, Iterator end, std::complex<double>& c){
		// Initialize the variables
		double rC = 0.0;
		double cC = 0.0;

		// Now call the parse function.
		qi::phrase_parse(
			start,
			end,

			// grammer of a complex number

			'(' >> qi::double_[phoenix::ref(rC) = qi::_1]
			>> -(',' >> qi::double_[phoenix::ref(cC) = qi::_1]) >> ')'
			| qi::double_[phoenix::ref(rC) = qi::_1],

			// Explain the grammer
			/*
				_1 is a placeholder which says that assign the first value to the argument at the left

				ref(rc) means that assign the reference of the variable rc the value of the argument in the right.

				- sign is used to tell that we need to find the argument for zero or one time.

				So the grammer can parse:
					- (12,45)
					- (12)
					- 13
			*/
			qi::space
		);

		if(start != end) {
			return false;
		}
		c = std::complex<double>(rC, cC);
		return true;

	}
}

int main() {
	std::string s;
	std::getline(std::cin, s);
	auto start = s.begin();
	std::complex<double> c;
	if(client::parseComplex(start, s.end(), c)){

		std::cout<< "Complex number is \n"<<c<<"\n";
	}
	return 0;
}
