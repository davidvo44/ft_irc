#include "Command.hpp"
#include <string>

void Command::PassCommand(Server &server, Client &sender, Message &message)
{
	message.parseNICK_USER_PASS();

	if (message.getParameter().empty() == true && server.getPassword().empty() == false)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getTarget(), sender.getNick());
	if (sender.getLogStep() != 0)
		throw ProtocolError(ERR_ALREADYREGISTERED, sender.getNick(), sender.getNick());
	if (server.getPassword().empty() == false && message.getParameter() != server.getPassword())
		throw ProtocolError(ERR_PASSWDMISMATCH, sender.getNick(), sender.getNick());
	sender.setLogStep(1);
}
