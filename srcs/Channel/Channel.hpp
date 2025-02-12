#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../Server/Server.hpp"

class Channel
{
private:
	std::string _name;
	std::map<int, Client> _Clients;
	std::string _topic;
public:
	Channel(std::string name, Client client);
	Channel();
	~Channel();
	void AddClient(Client client);
	void JoinChannel(Client client);
	void setTopic(const std::string topic);
	const std::string getTopic();
	std::map<int, Client> &GetClient();
};

#endif
