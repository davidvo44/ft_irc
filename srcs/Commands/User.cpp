#include "Command.hpp"

void Command::UserCommand(Client &sender, Message &message, Server &server)
{
	message.parseNICK_USER_PASS();
	if (sender.getLogStep() == 3)
		throw ProtocolError(ERR_ALREADYREGISTERED , sender.getNick(), sender.getNick());
	if (sender.getLogStep() == 0)
	{
		std::string response = "ERROR :You need to send PASS before USER\r\n";
		send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	if (sender.getLogStep() == 1)
	{
		std::string response = "ERROR :You need to send NICK before USER\r\n";
		send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	if (message.getParameter().empty()== true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getTarget(), sender.getNick());
	sender.setName(message.getParameter());
	sender.setLogStep(3);
	server.AcceptNewClient(sender.getFd());
	std::cout << "Login succesfull for : " << sender.getNick() << std::endl;
}
