#include "Command.hpp"

void Command::Nick(Message message, Client &sender, Server &server)
{
	int			fdcl;
	std::string	response;
	
	if (message.getContent().empty() == true)
		throw ProtocolError(431, message.getContent(), sender.GetNick());
	std::map<int, Client*>::iterator itcl = server.getClients().begin();
	for (;itcl != server.getClients().end(); itcl++)
	{
		if (itcl->second->GetNick() == message.getContent())
		throw ProtocolError(433, message.getContent(), sender.GetNick());
	}

	std::cout << "NICK cmd :" << std::endl;
	std::cout << ":" << sender.GetNick() << "!" << sender.GetName() << "@" << sender.GetIpAdd() << " NICK " << message.getContent() << std::endl;


	fdcl = sender.GetFd();
	response = GetPrefix(sender);
	response += "NICK " + message.getContent() + "\n";

	SendBySharedChannels(response, sender, server);

	send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	sender.SetNick(message.getContent());
}