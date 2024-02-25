#include "WikiManager.h"


void WikiManager::add_language_buttons(dpp::message& msg) {
	msg.add_component(
		dpp::component()
		.set_style(dpp::component_style::cos_success)
		.set_label("English")
		.set_id("wikibutton-viewin-english")


		.add_component(dpp::component()
			.set_style(dpp::component_style::cos_success)
			.set_label("Arabic")
			.set_id("wikibutton-viewin-arabic")

		).add_component(dpp::component()
			.set_style(dpp::component_style::cos_success)
			.set_label("Mandarian")
			.set_id("wikibutton-viewin-mandarian")

		).add_component(dpp::component()
			.set_type(dpp::cot_button)
			.set_style(dpp::component_style::cos_success)
			.set_label("Spanish")
			.set_id("wikibutton-viewin-spanish")
		).add_component(dpp::component()
			.set_style(dpp::component_style::cos_success)
			.set_label("French")
			.set_id("wikibutton-viewin-french")
		));
};

void WikiManager::replace_spaces(std::string& query) {
	std::cout << "Raw: " << query << "\n";
	while (query.find(" ") != std::string::npos) {
		query.replace(query.find(" "), 1, "_");
	};

};

void WikiManager::to_lower_case(std::string& query) {
	for (char& c : query) {
		if (int(c) >= 65 && int(c) <= 90) {
			c = char(int(c) + 32);
		};
	};
};

void WikiManager::format_query(std::string& query) {


	replace_spaces(query);
	to_lower_case(query);


	std::cout << "After formatting: " << query << "\n";

};