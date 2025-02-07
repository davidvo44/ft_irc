#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../Server/Server.hpp"

class Channel
{
private:
	std::string _name;
	std::map<int, Client> _Clients;
public:
	Channel(std::string name, Client client);
	Channel();
	~Channel();
	void AddClient(Client client);
	void JoinChannel(Client client);
	std::map<int, Client> &GetClient();
};

#endif