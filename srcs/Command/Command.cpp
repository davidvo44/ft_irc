#include "Command.hpp"
#include "vector"

void Command::CheckCommande(std::string str, Server &server, int fd)
{
	std::string array[] = {"JOIN", "USER", "NICK", "PASS", "PRIVMSG", "WHO", "PART"};
	int index = 0;
	Message str_message(str);
	
	/*static int count = 0;
	count++;
	std::cout << "COUNT : " << count << std::endl;
	if (count == 1)
	{
		std::cout << "SENT : " << ":garivo!garivo@127.0.0.1 JOIN test" << std::endl;
		write(fd, ":garivo!garivo@127.0.0.1 JOIN #SALEMERDE\n", 41);
	}
	else if (count == 1)
		write(fd, ":cringe!mecChelou@Shithole PRIVMSG garivo :Hello World\n", 56);
	else if (count == 3)
		write(fd, ":didier!con@Shithole JOIN #SALEMERDE\n", 37);
	else if (count == 2)
		//write(fd, ":didier!con@Shithole PRIVMSG #SALEMERDE :ALED\n", 46);
	else if (count == 2)
		write(fd, ":NickUser!User@127.0.0.1 PRIVMSG #SALEMERDE :Sac\n", 49);
	else if (count == 3)
		write(fd, ":NickUser!User@127.0.0.1 PRIVMSG #SALEMERDE :Sac\n", 49);
	else if (count == 4)
		write(fd, ":NickUser!User@127.0.0.1 PRIVMSG #SALEMERDE :Sac\n", 49);
	
	(void)str;
	(void)server;
	(void)index;*/
	while (index < 7)
	{
		if (str_message.getCommand().compare(array[index]) == 0)
			break;
		index++;
	}
	std::map<int, Client*>::iterator it = server.getClients().find(fd);
	try
	{
		switch (index)
		{
			case 0:
				Command::JoinChannel(*it->second, str_message.getContent(), server);
				break;
			case 1:
				std::cout << "attribute :" << str_message.getContent() << std::endl;
				(it->second)->SetName(str_message.getContent());
				break;
			case 2:
				Command::Nick(str_message, *it->second, server);
				break;
			case 3:
				(it->second)->SetPassword(str_message.getContent());
				break;
			case 4:
				Command::PrivateMessage(str_message, *it->second, server);
				break;
			case 5:
				Command::WhoCommand(fd, *(it->second), str_message, server);
				break;
			case 6:
				Command::Part(str_message, *it->second, server);
				break;
			default:
				throw ProtocolError(421, str, (it->second)->GetNick());
		}
	}
	catch(const std::exception& e)
	{
		Command::CatchErrors((it->second), e);
	}
}

void Command::CatchErrors(Client *client, const std::exception& e)
{
	Command::WritePrefix(client->GetFd(), *client);
	write (client->GetFd(), e.what(), strlen(e.what()));
	write (client->GetFd(), "\n", 1);

	Command::WritePrefix(1, *client);
	write (1, e.what(), strlen(e.what()));
	write (1, "\n", 1);
}

void Command::GetLineCommand(char *buffer, int fd, Server &server)
{
	std::string str;
	char *tmp = buffer;
	while (*tmp)
	{
		char *newline = strchr(tmp, '\n');
		if (newline)
		{
			*newline = '\0';
			Command::CheckCommande(str.append(tmp), server, fd);
			tmp = newline + 1;
			str.clear();
		}
		else
		{
			Command::CheckCommande(str.append(tmp), server, fd);
			break;
		}
	}
}

void Command::WritePrefix(int FdCl, Client client)
{
	std::string response = ":" + client.GetNick() + "!" + client.GetName() + "@" + client.GetIpAdd() + " ";
	send(FdCl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
