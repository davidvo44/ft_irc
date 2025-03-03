#include "Command.hpp"

void Command::ChessCommand(Server &server, Client &sender, Message &message)
{
	Channel *chan = server.getChannel().findValue(message.getTo());
	if (chan == NULL)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getContent(), sender.GetNick());
	if (message.getContent().empty() == true)
	{
		chan->getBot()->PrintChess(sender.GetFd());
		return ;
	}
	if (message.getContent() == "join")
	{
		chan->getBot()->JoinChess(sender.GetFd());
		return;
	}
	chan->getBot()->Ongame(sender.GetFd(), message);
}