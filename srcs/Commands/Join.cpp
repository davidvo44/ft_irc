
#include "Command.hpp"
#include "MutantMap.hpp"

static void checkmodechann(Client &client, Channel &channel, const std::string password);
static void write_channel(Client &client, const std::string target, Channel &chan);
static void parseJoinCmd(const std::string target, const std::string password, Message &message, Client &client, Server &server);

void Command::joinChannel(Client &client, Message& message, Server &server)
{
	if (client.getLogStep() != 3)
		throw ProtocolError(ERR_NOTREGISTERED, client.getNick(), client.getNick());
	std::map<std::string, std::string>* messageJoin = message.parseJOIN();
	if (!messageJoin)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), client.getNick());
	std::map<std::string, std::string>::iterator it = messageJoin->begin();
	while (it != messageJoin->end())
	{
		if (it->first.empty() == false)
			parseJoinCmd(it->first, it->second, message, client, server);
		it++;
	}
}

static void parseJoinCmd(const std::string target, const std::string password, Message &message, Client &client, Server &server)
{
	if (target.find_first_of("#&") != 0 || target.find_first_of(" ,") != std::string::npos)
		throw ProtocolError(ERR_BADCHANMASK, target, client.getNick());
	Channel *channel = server.getChannel().findValue(target);
	if (channel != NULL)
	{
		checkmodechann(client, *channel, password);
		channel->joinChannel(&client);
		std::cout << client.getName() << " join " << target << std::endl;
	}
	else
	{
		std::cout << "creating " << target << std::endl;
		server.getChannel()[target] = server.CreateChannel(&client, target);
		channel = server.getChannel().findValue(target);
	}
	write_channel(client, target, *channel);
	Command::getTopic(message, client, *channel);
}

static void checkmodechann(Client &client, Channel &channel, const std::string password)
{
	if (channel.viewMode('i') == true)
	{
		if (channel.isInWhitelist(client.getFd()) == false)
			throw ProtocolError(ERR_INVITEONLYCHAN, channel.getName(), client.getNick());
	}
	if (channel.viewMode('k') == true)
	{
		if (password != channel.getSuffixword())
			throw ProtocolError(ERR_BADCHANNELKEY, channel.getName(), client.getNick());
	}
	if (channel.viewMode('l') == true)
	{
		if ((int)channel.getClient().size() >= channel.getMaxclient())
			throw ProtocolError(ERR_CHANNELISFULL, channel.getName(), client.getNick());
	}
}

static void write_channel(Client &client, const std::string target, Channel &chan)
{
	std::string response;
	unsigned idx = 0;
	while (chan[idx])
	{
		int fdcl = chan[idx]->getFd();
		response = client.getPrefix() + "JOIN " + target + "\r\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		idx++;
	}
}
