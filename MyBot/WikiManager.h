#include <iostream>
#include <dpp/dpp.h>
class WikiManager {
public:
	void format_query(std::string& query);
	void add_language_buttons(dpp::message& msg);
	void replace_spaces(std::string& query);
	void to_lower_case(std::string& query);
};

