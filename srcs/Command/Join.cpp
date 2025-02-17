#include "Command.hpp"

static void write_channel(Client client, std::string ChName, Server &server);

void Command::JoinChannel(Client client, std::string ChName, Server &server)
{
	std::map<std::string, Channel>::iterator it = server.getChannel().find(ChName);
	if (ChName.find('#') != 0 && ChName.find('&') != 0)
		throw ProtocolError(403, ChName, client.GetNick());
    if (server.getChannel().empty() == false &&  it != server.getChannel().end())
	{
       it->second.JoinChannel(client);
	   std::cout << client.GetName() << " join " << ChName << std::endl;
    }
	else
	{
		std::cout << "creating " << ChName << std::endl;
		server.getChannel()[ChName] = server.CreateChannel(client, ChName);
    }
	write_channel(client, ChName, server);
}

static void write_channel(Client client, std::string ChName, Server &server)
{
	//:Nick!User@Host JOIN #general
	std::map<int, Client*>::iterator itclient = server.getClients().begin();
	while (itclient != server.getClients().end())
	{
		int fdcl = itclient->second->GetFd();
		std::string response = "JOIN " + ChName + "\n";
		Command::WritePrefix(fdcl, client);
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		RplMessage::GetRply(331, fdcl, 2, client.GetNick().c_str(), ChName.c_str());
		write (fdcl, "\n", 1);
		itclient++;
	}
	std::string response = "JOIN " + ChName + "\n";
	Command::WritePrefix(1, client);
	send(1, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	RplMessage::GetRply(331, 1, 2, client.GetNick().c_str(), ChName.c_str());
}