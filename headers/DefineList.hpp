
#ifndef DEFINELIST_HPP
# define DEFINELIST_HPP


#define	ERR_UNKNOWNCOMMAND 421

//			WELCOME			//
#define RPL_WELCOME(target) (":irc.com 001 " + target + " :Welcome to ft_irc " + target + "!!!" + "\r\n")
#define RPL_YOURHOST(target) (":irc.com 002 " + target + " :Your host is irc.com, running version ft_irc" + "\r\n")
#define RPL_CREATED(target) (":irc.com 003 " + target + " :This server was created today" + "\r\n")
#define RPL_MYINFO(target) (":irc.com 004 " + target + " :irc.com ft_irc io tkl" + "\r\n")

//			JOIN			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_NOSUCHCHANNEL 403
#define	ERR_TOOMANYCHANNELS 405
#define	ERR_BADCHANNELKEY 475
#define	ERR_BANNEDFROMCHAN 474 -
#define	ERR_CHANNELISFULL 471
#define	ERR_INVITEONLYCHAN 473
#define	ERR_BADCHANMASK 476
#define	RPL_TOPICWHOTIME 333


//			USER			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_ALREADYREGISTERED 462


//			NICK			//
#define	ERR_NONICKNAMEGIVEN 431
#define	ERR_ERRONEUSNICKNAME 432
#define	ERR_NICKNAMEINUSE 433
#define	ERR_NICKCOLLISION 436


//			PASS			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_ALREADYREGISTERED 462
#define	ERR_PASSWDMISMATCH 464


//			PRIVMSG			//
#define	ERR_NOSUCHNICK 401
#define	ERR_NOSUCHSERVER 402
#define	ERR_CANNOTSENDTOCHAN 404
#define	ERR_TOOMANYTARGETS 407
#define	ERR_NORECIPIENT 411
#define	ERR_NOTEXTTOSEND 412
#define	ERR_NOTOPLEVEL 413
#define	ERR_WILDTOPLEVEL 414
#define	RPL_AWAY 301


//			WHO				//
#define	RPL_WHOREPLY 352
#define	RPL_ENDOFWHO 315
#define	RPL_NAMREPLY(target, channel, nick, flag) (":irc.com 353 " + target + " = " + channel + " :" + flag + nick + "\r\n")
#define	RPL_ENDOFNAMES(channel) (":irc.com 366 " + channel + " :End of NAMES list" + "\r\n")


//			PART			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_NOSUCHCHANNEL 403
#define	ERR_NOTONCHANNEL 442


//			TOPIC			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_NOSUCHCHANNEL 403
#define	ERR_NOTONCHANNEL 442
#define	ERR_CHANOPRIVSNEEDED 482
#define	RPL_NOTOPIC(target, channel) (":irc.com 331 " + target + " " + channel + " :No topic is set" + "\r\n")
#define	RPL_TOPIC(target, channel, topic) (":irc.com 332 " + target + " " + channel + " :" + topic + "\r\n")
#define	RPL_TOPICWHOTIME 333


//			KICK			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_NOSUCHCHANNEL 403
#define	ERR_CHANOPRIVSNEEDED 482
#define	ERR_USERNOTINCHANNEL 441
#define	ERR_NOTONCHANNEL 442


//			INVITE			//
#define	RPL_INVITING(source, channel, target) (":irc.com 331 " + target + " " + channel + " :No topic is set" + "\r\n")
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_NOSUCHCHANNEL 403
#define	ERR_NOTONCHANNEL 442
#define	ERR_CHANOPRIVSNEEDED 482
#define	ERR_USERONCHANNEL 443


//			MODE			//
//			USER MODE		//
#define	ERR_NOSUCHNICK 401
#define	ERR_USERSDONTMATCH 502
#define	RPL_UMODEIS 221
#define	ERR_UMODEUNKNOWNFLAG 501
//			CHANNEL MODE	//
#define	ERR_NOSUCHCHANNEL 403
#define	RPL_CHANNELMODEIS(target, channel, mode) (":irc.com 324 " + target + " " + channel + " " + mode + "\r\n")
#define	RPL_CREATIONTIME 329
#define	ERR_UNKNOWNMODE 472
#define	ERR_CHANOPRIVSNEEDED 482


//			CAP				//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_ALREADYREGISTERED 462
#define	ERR_PASSWDMISMATCH 464
#define ERR_NOTREGISTERED 451



#endif
