
#include "Command.hpp"
//:thierry!user@host QUIT :Bye !
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
}

void Command::QuitClient(int fd, Poll &poll, size_t i)
{
	std::cout << "Client disconnected." << std::endl;
	close(fd);
	poll.getPollfd().erase(poll.getPollfd().begin() + i);
}
