#include "Command.hpp"

void Command::JoinChannel(Client client, std::string ChName, Server &server)
{
	std::map<std::string, Channel>::iterator it = server.getChannel().find(ChName);
	if (ChName.find('#') != 0 && ChName.find('&') != 0)
		throw ProtocolError(403, ChName, client.GetNick());
    if (server.getChannel().empty() == false &&  it != server.getChannel().end())
	{
		// if (it->second.GetClient().find(client.GetFd()) != it->second.GetClient().end())
		// {
		// 	write (client.GetFd(), "Channel already joined\n", 23);
		// 	return;
		// }
       it->second.JoinChannel(client);
	   std::cout << client.GetName() << " join " << ChName << std::endl;
    }
	else
	{
		std::cout << "creating " << ChName << std::endl;
		server.getChannel()[ChName] = server.CreateChannel(client, ChName);
    }
	//:Nick!User@Host JOIN #general
	std::map<int, Client*>::iterator itclient = server.getClients().begin();
	while (itclient != server.getClients().end())
	{
		int fdcl = itclient->second->GetFd();
		WritePrefix(fdcl, client);
		write (fdcl, "JOIN ", 5);
		write (fdcl, ChName.c_str(), strlen(ChName.c_str()));
		write (fdcl, "\n", 1);
		itclient++;
	}
	WritePrefix(1, client);
	write (1, "JOIN ", 5);
	write (1, ChName.c_str(), strlen(ChName.c_str()));
	write (1, "\n", 1);
}
