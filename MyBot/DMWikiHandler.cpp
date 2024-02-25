#include "DMWikiHandler.h"



DMWikiHandler::DMWikiHandler(dpp::cluster& cluster) {

	cluster.on_message_create([this, &cluster](const dpp::message_create_t& event) -> dpp::task<void> {
		if (event.msg.content == "end") {
			exit(0);
		}
		if (event.msg.is_dm() && !(event.msg.author.is_bot())) {
			std::string content = event.msg.content;
			format_query(content);
			dpp::http_request_completion_t cc = co_await cluster.co_request("https://en.wikipedia.org/api/rest_v1/page/summary/" + content,
				dpp::http_method::m_get, "", "application/json", {}, "1.0");

			// Setting the default embed first
			dpp::embed wiki_embed;
			wiki_embed.set_footer("WikiHub", cluster.me.get_avatar_url());



			// Constructing the root and the reader objects
			Json::Value value;
			Json::Reader reader;


			// Using the Reader::parse(); to read our cpr::Response::text into Json::Value 
			bool parsing_successful = reader.parse(cc.body, value);

			bool succeed = (cc.status == 200 && parsing_successful == true) ? true : false;
			if (succeed) {

				Json::Value::Members members = value.getMemberNames();
				for (auto it = members.begin(); it < members.end(); it++) {
					if (it->_Equal("originalimage"))
						wiki_embed.set_image(value.get("originalimage", "Not found").get("source", "No image").asString());
				}
				wiki_embed.set_title(value.get("titles", "Not found").get("normalized", "Not found").asString());
				wiki_embed.set_description(value.get("extract", "Not found").asString());



				dpp::message message;

				message.add_embed(wiki_embed);



				add_language_buttons(message);

				event.reply(message);
			}
			else {
				event.reply("**Sorry, I couldn't find your query on wikipedia.**");
			}


		};


		});





	// Handling langauge switching of DM WIKIs
	cluster.on_button_click([&](const dpp::button_click_t& event) {
		event.reply();
		dpp::message original_message = event.command.get_context_message();

		std::string content = original_message.embeds[0].title;
		std::cout << "CONTENT: " << content;
		//format_query(content);
		replace_spaces(content);
		std::map<std::string, std::string> lang_map{
			{"wikibutton-viewin-english", "en"},
			{"wikibutton-viewin-arabic", "ar"},
			{"wikibutton-viewin-mandarian", "zh"},
			{"wikibutton-viewin-spanish", "es"},
			{"wikibutton-viewin-french", "fr"}
		};
		std::string https_url = "https://" + lang_map[event.custom_id] + ".wikipedia.org/api/rest_v1/page/summary/" + content;
		std::cout << "HTTPS request sent to: " << https_url << "\n";
			cluster.request(https_url,
				dpp::http_method::m_get, [&](const dpp::http_request_completion_t& hcallback) {
					std::cout << "BODY: " << hcallback.body << "\n";
					//Setting the default embed first
					dpp::embed wiki_embed;
					wiki_embed.set_footer("WikiHub", cluster.me.get_avatar_url());



					// Constructing the root and the reader objects
					Json::Value value;
					Json::Reader reader;


					//Using the Reader::parse(); to read our cpr::Response::text into Json::Value 
					bool parsing_successful = reader.parse(hcallback.body, value);


					if (parsing_successful) {
						Json::Value::Members members = value.getMemberNames();
						for (auto it = members.begin(); it < members.end(); it++) {
							if (it->_Equal("originalimage"))
								wiki_embed.set_image(value.get("originalimage", "Not found").get("source", "No image").asString());
						}
						wiki_embed.set_title(value.get("titles", "Not found").get("normalized", "Not found").asString());
						wiki_embed.set_description(value.get("extract", "Not found").asString());





						original_message.add_embed(wiki_embed);


						cluster.message_edit(original_message);
					}
					else {
						//event.reply("Sorry, couldn't find this specified query in the chosen language.");
					}
				}, "", "application/json", {}, "1.0");
			
			

		});

}