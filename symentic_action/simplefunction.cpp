#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/config/warning_disable.hpp>

namespace client {
	namespace qi = boost::spirit::qi;

	void print(int const& i) {
		std::cout<<i;
	}
	using boost::spirit::qi::phrase_parse;
	using boost::spirit::qi::int_;
	using boost::spirit::qi::space;
	template <typename Iterator>
	void parseString(Iterator start, Iterator end) {
		qi::phrase_parse(
			start,
			end,
			'{' >> int_[&print] >> '}',
			space
		);
	}
}

int main(){
	using client::parseString;

	std::cout<<"Enter a string of type '{44}'";
	std::string s;
	std::getline(std::cin, s);

	parseString(s.begin(), s.end());
	return 0;
}
