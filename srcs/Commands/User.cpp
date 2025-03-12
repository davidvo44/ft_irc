#include "Command.hpp"

void Command::UserCommand(Client &sender, Message &message, Server &server)
{
	message.parseNICK_USER_PASS();
	if (sender.getLogStep() == 3)
		throw ProtocolError(ERR_ALREADYREGISTERED , sender.getNick(), sender.getNick());
	if (sender.getLogStep() != 2)
	throw ProtocolError(ERR_ALREADYREGISTERED , sender.getNick(), sender.getNick());
	if (message.getParameter().empty()== true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getTarget(), sender.getNick());
	sender.setName(message.getParameter());
	sender.setLogStep(3);
	server.AcceptNewClient(sender.getFd(), sender.getIpAddr());
}
