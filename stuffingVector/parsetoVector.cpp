#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

namespace client {
	namespace qi = boost::spirit::qi;
	namespace phoenix = boost::phoenix;

	template <typename Iterator>
	bool parseString(Iterator start, Iterator end, std::vector<double>& v) {
		using phoenix::push_back;
		qi::phrase_parse(
			start,
			end,

			// Begin grammer
			(
				'(' >> qi::double_[push_back(phoenix::ref(v), qi::_1)]
				>> *(',' >> qi::double_[push_back(phoenix::ref(v), qi::_1)])
				>> ')'
			)
			,
			// End grammer
			qi::space
		);

		if(start != end) {
			return false;
		}
		return true;
	}
}

int main() {

	std::string s;
	std::getline(std::cin, s);
	auto start = s.begin();
	
	std::vector<double> v;	
	if(client::parseString(start, s.end(), v)) {
		for (std::vector<double>::size_type i = 0; i < v.size(); ++i)
                	std::cout << i+1 << ": " << v[i] << std::endl;
	}
	return 0;
}
