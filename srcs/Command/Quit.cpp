#include "Command.hpp"

void Command::QuitClient(int fd, Poll &poll, size_t i)
{
	std::cout << "Client disconnected." << std::endl;
	close(fd);
	poll.getPollfd().erase(poll.getPollfd().begin() + i);
	std::map<int, Client*>::iterator it = poll.getServer().getClients().find(fd);
	it->second->setLog(false);
}