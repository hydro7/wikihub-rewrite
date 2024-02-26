#include "WikiHub.h"

int main() {
	
	std::string BOT_TOKEN= "MTA0MDE4NzU5MTU1MjY3MTc0NA.GbirYy.gczrHrhGXBZ218FcnBTBceLMAI-zYBWHHjy3_A";

	std::cout << "WikiHub class's constructor called." << "\n";
	dpp::cluster cluster(BOT_TOKEN, dpp::intents::i_direct_messages);
	/* Output simple log messages to stdout */
	cluster.on_log(dpp::utility::cout_logger());

	cluster.on_ready([&cluster](const dpp::ready_t& event) {
		
		cluster.current_user_get_guilds([&](const dpp::confirmation_callback_t& callback) {
			if (!callback.is_error()) {
				dpp::guild_map guild_map = callback.get<dpp::guild_map>();
				
				std::cout << "(S/O)------------- Guild(" << guild_map.size() << ") list -------------(S/O)" << "\n";
				// Down below are example loops
				//1. range-based for-loop
				for (auto guild_iterator = guild_map.begin(); guild_iterator != guild_map.end(); guild_iterator++) {
					std::cout << guild_iterator->second.name << "\n";
				}

				// 2. Traversing using begin() and end() with a lambda
				//std::for_each(guild_map.begin(), guild_map.end(), [](std::pair<dpp::snowflake, dpp::guild> p) {
						//std::cout << p.first << "::" << p.second.name << "\n";
					//}
				//);
			

				// using iterator

				/*std::unordered_map<dpp::snowflake, dpp::guild>::iterator it = guild_map.begin();

				while (it != guild_map.end()) {
					std::cout << (*it).second.name << "\n";

					it++;
				}*/
				
				std::cout << "(S/O)------------- Guild(" << guild_map.size() << ") list -------------(S/O)" << "\n";

			}
			});

		

	});
	DMWikiHandler wiki_handler(cluster);
	cluster.start(dpp::st_wait);
	return 0;
}


/* Register slash command here in on_ready */
		//bot.on_ready([&bot](const dpp::ready_t& event) {
		//	/* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
		//	if (dpp::run_once<struct register_bot_commands>()) {
		//		std::vector<dpp::slashcommand> commands{
		//			{ "ping", "Ping pong!", bot.me.id }
		//		};

		//		bot.global_bulk_command_create(commands);
		//	}


			/*co_current_user_get_guilds()[](dpp::cluster::current_user_get_guilds& guilds) {

				};*/
				//codpp::cluster::co_current_user_get_guilds();




		   /* Handle slash command with the most recent addition to D++ features, coroutines! */
		   /*bot.on_slashcommand([](const dpp::slashcommand_t& event) -> dpp::task<void> {
			   if (event.command.get_command_name() == "ping") {
				   co_await event.co_reply("Pong!");
			   }
			   co_return;
			   });*/