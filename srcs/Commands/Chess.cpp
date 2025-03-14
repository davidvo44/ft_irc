
#include "Command.hpp"

static bool check_parse(int fd, Message &message, Channel &chan);
static bool sendError(std::string response, int fd, std::string chan);

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
	if (message.getParameter() == "leave")
	{
		chan->getBot()->StartGame();
		return;
	}
	if (check_parse(sender.getFd(), message, *chan) == false)
		return;
	chan->getBot()->Ongame(sender.getFd(), message);
}

static bool check_parse(int fd, Message &message, Channel &chan)
{
	if (fd != chan.getBot()->getBlackFd() && fd != chan.getBot()->getWhiteFd())
		return sendError("You're not playing\n", fd, chan.getName());
	if (message.getParameter().size() != 2 || message.getSuffix().size() != 2 )
		return sendError("Wrong Position\n", fd, chan.getName());
	if (message.getParameter()[0] < 'A' || message.getParameter()[0] > 'H' || \
	message.getSuffix()[0] < 'A' || message.getSuffix()[0] > 'H')
		return sendError("Wrong Position\n", fd, chan.getName());
	if (message.getParameter()[0] < 'A' || message.getParameter()[0] > 'H' || \
	message.getSuffix()[0] < 'A' || message.getSuffix()[0] > 'H')
		return sendError("Wrong Position\n", fd, chan.getName());
	return true;
}

static bool sendError(std::string reason, int fd, std::string chan)
{
	std::string prefixmsg = ":Chess!Chess@127.0.0.1 PRIVMSG " + chan + " ";
	std::string response;
	response = prefixmsg + reason;
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	return false;
}
