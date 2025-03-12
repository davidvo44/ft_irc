
#include "Command.hpp"
//: thierry!user@host QUIT :Bye !

static void eraseClient(int fd, Server &server);

void Command::QuitCommand(Server &server, Client &sender, Message &message)
{
	message.parseQUIT();

	std::string response = sender.getPrefix() + "QUIT :";
	if (message.getParameter().empty() == true)
		response += "bye\n";
	else
		response += message.getParameter();
	std::cout << "MESSAGE IS: " << response << std::endl;
	Command::SendBySharedChannels(response, sender, server);
	eraseClient(sender.getFd(), server);
}

void Command::QuitClientfromPoll(int fd, Server &server)
{
	Client *sender = server.getClients().findValue(fd);

	std::string response = sender->getPrefix() + "QUIT :bye\n";
	Command::SendBySharedChannels(response, *sender, server);
	eraseClient(fd, server);
}

static void eraseClient(int fd, Server &server)
{
	std::map<std::string, Channel *>::iterator it = server.getChannel().begin();
	for (; it != server.getChannel().end(); it++)
	{
		if (it->second->getClient().findValue(fd))
			it->second->partChannel(*(it->second->getClient().findValue(fd)));
	}
	Client *clToDel = server.getClients().findValue(fd);
	server.getClients().erase(fd);
	delete clToDel;
	close(fd);
}