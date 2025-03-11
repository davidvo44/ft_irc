#include "Command.hpp"
#include <string>

void Command::PassCommand(Server &server, Client &sender, Message &message)
{
	message.parseNICK_USER_PASS();
	// std::string response;
	if (message.getParameter().empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getTarget(), sender.getNick());
	if (sender.getLogStep() != 0)
		throw ProtocolError(ERR_ALREADYREGISTERED, sender.getNick(), sender.getNick());
	if (message.getParameter() == server.getPassword())
	{
		sender.setLogStep(1);
		return;
	}
	// std::stringstream ss;
	// for (int i = 3; i != 0; i--)
	// {
	// 	ss << i;
	// 	std::cout << i << std::endl;
	// 	response = "Wrong password, " + ss.str() + " retry left\n";
	// 	send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	// 	response = "PASS: ";
	// 	send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	// 	std::string input;
	// 	if (!std::getline(sender.getFd(), input))
	//	 	exit (0);
	// 	if (message.getParameter() == server.getPassword())
	// 	{
	// 		sender.setLogStep(1);
	// 		return;
	// 	}
	// }
	if (message.getParameter() != server.getPassword())
		throw ProtocolError(ERR_PASSWDMISMATCH, sender.getNick(), sender.getNick());
	sender.setLogStep(1);
}
