
#ifndef ULTIMATE_DEFINE_LIST_HPP
#define UTLTIMATE_DEFINE_LIST_HPP

#define CRLF "\r\n"
#define CRLF_LEN 2
#define MAX_USERLIMIT 100
#define NICK_FORBIDDEN_CHAR "*:'\"&#~@$!;?./§%µ£¤|°<>"

// #define DEFAULT_OPER_NAME "bober"
// #define DEFAULT_OPER_PASS "bober"
// #define DEFAULT_OPER_HOST "localhost"

// #define DEFAULT_QUIT_RPL "For no reason"
// #define DEFAULT_SHUTDOW_RPL "Server shuting down"

#define PRIVMSG(source, target, msg) (":" + source + " PRIVMSG " + target + " " + msg + CRLF)
#define JOIN_MSG(source, channel) (":" + source + " JOIN " + channel + CRLF)
#define KICK_MSG(source, channel, target, comment) (":" + source + " KICK " + channel + " " + target + " " + comment + CRLF)
#define MODE_MSG(source, channel, mode, mode_params) (":" + source + " MODE " + channel + " " + mode + " " + mode_params + CRLF)
#define NICK_MSG(source, nick) (":" + source + " NICK " + nick + CRLF)
#define PART_MSG(source, channel) (":" + source + " PART " + channel + CRLF)
#define TOPIC_MSG(source, channel, topic) (":" + source + " TOPIC " + channel + " :" + topic + CRLF)
#define QUIT_MSG(source, reason) (":" + source + " QUIT " + ":QUIT: " + reason + CRLF)
#define ERROR_QUIT() ("ERROR :Connection terminated by peer\r\n")
#define INVITE_MSG(source, nick, channel) (":" + source + " INVITE " + nick + " " + channel + CRLF)
#define KILL_MSG(source, nick, reason) (":" + source + " KILL " + nick + " " + reason + CRLF)

/*#define RPL_CHANNELMODEIS(channel, mode, mode_params) ("324 " + channel + " " + mode + " " + mode_params)*/

#define ERR_NOSUCHNICK(source, nick) ("401 " + source + " " + nick + " :No such nickname" + CRLF)
#define ERR_NOSUCHSERVER(source, server) ("402 " + source + " " + server + " :No such server" + CRLF)
#define ERR_NOSUCHCHANNEL(source, channel) ("403 " + source + " " + channel + " :No such Channel" + CRLF)
#define ERR_CANNOTSENDTOCHAN(source, channel) ("404 " + source + " " + channel + " :Cannot send to channel" + CRLF)
#define ERR_TOOMANYCHANNEL(source, channel) ("405 " + source + " " + channel + " :You have joined too many channels" + CRLF)
#define ERR_WASNOSUCHNICK(source, nick) ("406 " + source + " " + nick + " :There was no such nickname" + CRLF)
#define ERR_TOOMANYTARGETS(source, target) ("407 " + source + " " + target + " :Duplicate recipients. No message deflivered" + CRLF)
#define ERR_NOORIGIN(source) ("408 " + source + " :No origin specified" + CRLF)
#define ERR_NORECIPIENT(source, command) ("411 " + source + " :No recipient give (" + command + ")" + CRLF)
#define ERR_NOTEXTTOSEND(source) ("412 " + source + " :No text to send" + CRLF)
#define ERR_NOTOPLEVEL(source, mask) ("413 " + source + " " + mask + " :No toplevel domain specified" + CRLF)
#define ERR_WILDTOPLEVEL(source, mask) ("414 " + source + " " + mask + " :Wildcard in toplevel domain" + CRLF)
#define ERR_UNKNOWNCOMMAND(source, command) ("421 " + source + " " + command + " :Unknown command" + CRLF)
#define ERR_NOMOTD(source) ("422 " + source + " :MOTD File is missing" + CRLF)
#define ERR_NOADMININFO(source, server) ("423 " + source + " " + server + " :No administrative info available" + CRLF)
#define ERR_FILEERROR(source, operation, file) ("424 " + source + " :File error doing " + operation + " on " + file + CRLF)
#define ERR_NONICKNAMEGIVEN(source) ("431 " + source + " :No nickname given" + CRLF)
#define ERR_ERRONEUSNICKNAME(source, nick) ("432 " + source + " " + nick + " :Erroneus nickname" + CRLF)
#define ERR_NICKNAMEINUSE(source, nick) ("433 " + source + " " + nick + " :Nickname is already in use" + CRLF)
#define ERR_NICKCOLLISION(source, nick) ("436 " + source + " " + nick + " :Nickname collision KILL" + CRLF)
#define ERR_USERNOTINCHANNEL(source, nick, channel) ("441 " + source + " " + nick + " " + channel + " :They aren't in that channel" + CRLF)
#define ERR_NOTONCHANNEL(source, channel) ("442 " + source + " " + channel + " :You're not on that channel" + CRLF)
#define ERR_USERONCHANNEL(source, user, channel) ("443 " + source + " " + user + " " + channel + " :is already on channel" + CRLF)
#define ERR_NOLOGIN(source, user) ("444 " + source + " " + user + " :User not logged in" + CRLF)
#define ERR_SUMMONDISABLED(source) ("445 " + source + " :SUMMON has been disabled" + CRLF)
#define ERR_USERSDISABLED(source) ("446 " + source + " :USERS has been disabled" + CRLF)
#define ERR_NOTREGISTERED(source) ("451 " + source + " :You have not registered" + CRLF)
#define ERR_NEEDMOREPARAMS(source, command) ("461 " + source + " " + command " :Not enough parameters" + CRLF)
#define ERR_ALREADYREGISTERED(source) ("462 " + source + " :You are already registered, you may not register" + CRLF)
#define ERR_NOPERMFORHOST(source) ("463 " + source + " :Your host isn't among the privileged" + CRLF)
#define ERR_PASSDMISMATCH(source) ("464 " + source + " :Password incorrect" + CRLF)
#define ERR_YOUREBANNEDCREEP(source) ("465 " + source + " :Your are banned from this server" + CRLF)
#define ERR_KEYSET(source, channel) ("467 " + source + " " + channel + " :Channel key already set" + CRLF)
#define ERR_CHANNELISFULL(source, channel) ("471 " + source + " " + channel + " :Cannot join channel (+l)" + CRLF)
#define ERR_UNKNOWNMODE(source, mode) ("472 " + source + " " + mode + " :is unknown mode char for me" + CRLF)
#define ERR_INVITEONLYCHAN(source, channel) ("473 " + source + " " + channel + " :Cannot join channel (+i)" + CRLF)
#define ERR_BANNEDFROMCHAN(source, channel) ("474 " + source + " " + channel + " :Cannot join channel (+b)" + CRLF)
#define ERR_BADCHANNELKEY(source, channel) ("475 " + source + " " + channel + " :Cannot join channel (+k)" + CRLF)
#define ERR_BADCHANMASK(source, channel) ("476 " + source + " " + channel + " :Bad channel mask" + CRLF)
#define ERR_NOPRIVILEGES(source) ("481 " + source + " :Permission Denied- You're not an IRC operator" + CRLF)
#define ERR_CHANOPRIVSNEEDED(source, channel) ("482 " + source + " " + channel + " :You're not channel operator" + CRLF)
#define ERR_CANTKILLSERVER(source) ("483 " + source + " :You can't kill a server!" + CRLF)
#define ERR_NOOPERHOST(source) ("491 " + source + " :No O-lines for your host" + CRLF)
#define ERR_UMODEUKNOWNFLAG(source) ("501 " + source + " :Unknown MODE flag" + CRLF)
#define ERR_USERSDONTMATCH(source) ("502 " + source + " Can't change mode for others users" + CRLF)


#define RPL_WELCOME(source) ("001 " + source + " :Welcome to ft_irc " + source + "!!!" + CRLF)

#define RPL_NONE(source) ("300 " + source + CRLF)

#define RPL_NOTOPIC(source, channel) ("331 " + source + " " + channel + " :No topic is set" + CRLF)
#define RPL_TOPIC(source, channel, topic) ("332 " + source + " " + channel + " :" + topic + CRLF)

#define RPL_INVITING(source, channel, nick) ("341 " + source + " " + nick + " " + channel + CRLF)
#define RPL_CHANNELMODEIS(source, channel, mode, mode_params) ("324 " + source + " " + channel + " " + mode + " " + mode_params + CRLF)
// #define RPL_CHANNELMODEIS(channel, mode,)

#define RPL_NAMREPLY(source, channel, nick, flag) ("353 " + source + " = " + channel + " :" + flag + nick + CRLF)
#define RPL_ENDOFNAMES(source, channel) ("366 " + channel + " :End of /NAMES list" + CRLF)

#define RPL_LISTSTART(source) ("321 " + source + " Channel :Users Name" + CRLF)
#define RPL_LIST(source, channel, count, topic) ("322 " + source + " " + channel + " " + count + " :" + topic + CRLF)
#define RPL_LISTEND(source) ("323 " + source + " :End of /LIST" + CRLF)

#define RPL_WHOREPLY(source, channel, user, host, server, nick, flags, realname) ("352 " + source + " " + channel + " " + user + " " + host + " " + server + " " + nick + " H" + flags + " :1 " + realname + CRLF)
#define RPL_ENDOFWHO(source, name) ("315 " + source + " " + name + " :End of /WHO list" + CRLF)

#define RPL_WHOISUSER(source, nick, user, host, realname) ("311 " + source + " " + nick + " " + user + " " + host + " * :" + realname + CRLF)
#define RPL_WHOISCHANNELS(source, nick, flag, channel) ("319 " + source + " " + nick + " :" + flag + channel + CRLF)
#define RPL_WHOISSERVER(source, nick, serverName, serverInfo) ("312 " + source + " " + nick + " " + serverName + " :" + serverInfo + CRLF)
#define RPL_ENDOFWHOIS(source, nick) ("318 " + source + " " + nick + " :END of /WHOIS list" + CRLF)

#define RPL_YOUROPER(source) ("381 " + source +" :You are now an IRC operator" + CRLF)

#endif
