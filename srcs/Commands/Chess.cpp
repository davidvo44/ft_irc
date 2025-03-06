
#include "Command.hpp"

void Command::ChessCommand(Server &server, Client &sender, Message &message)
{
	message.parseCHESS();
	Channel *chan = server.getChannel().findValue(message.getTarget());
	if (chan == NULL)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getParameter(), sender.getNick());
	if (message.getParameter().empty() == true)
	{
		chan->getBot()->PrintChess(sender.getFd());
		return ;
	}
	if (message.getParameter() == "join")
	{
		chan->getBot()->JoinChess(sender.getFd());
		return;
	}
	chan->getBot()->Ongame(sender.getFd(), message);
}
