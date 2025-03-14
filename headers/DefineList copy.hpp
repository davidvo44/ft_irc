/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefineList.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:12:18 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 06:15:42 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINELIST_HPP
# define DEFINELIST_HPP


#define	ERR_UNKNOWNCOMMAND 421

//			WELCOME			//
#define	RPL_WELCOME 001
#define RPL_YOURHOST 002
#define RPL_CREATED 003
#define RPL_MYINFO 004

//			JOIN			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_NOSUCHCHANNEL 403
#define	ERR_TOOMANYCHANNELS 405
#define	ERR_BADCHANNELKEY 475
#define	ERR_BANNEDFROMCHAN 474 -
#define	ERR_CHANNELISFULL 471
#define	ERR_INVITEONLYCHAN 473
#define	ERR_BADCHANMASK 476
#define	RPL_TOPIC 332
#define	RPL_TOPICWHOTIME 333
#define	RPL_NAMREPLY 353
#define	RPL_ENDOFNAMES 366


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


//			PART			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_NOSUCHCHANNEL 403
#define	ERR_NOTONCHANNEL 442


//			TOPIC			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_NOSUCHCHANNEL 403
#define	ERR_NOTONCHANNEL 442
#define	ERR_CHANOPRIVSNEEDED 482
#define	RPL_NOTOPIC 331
#define	RPL_TOPIC 332
#define	RPL_TOPICWHOTIME 333


//			KICK			//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_NOSUCHCHANNEL 403
#define	ERR_CHANOPRIVSNEEDED 482
#define	ERR_USERNOTINCHANNEL 441
#define	ERR_NOTONCHANNEL 442


//			INVITE			//
#define	RPL_INVITING 341
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
#define	RPL_CHANNELMODEIS 324
#define	RPL_CREATIONTIME 329
#define	ERR_UNKNOWNMODE 472
#define	ERR_CHANOPRIVSNEEDED 482


//			CAP				//
#define	ERR_NEEDMOREPARAMS 461
#define	ERR_ALREADYREGISTERED 462
#define	ERR_PASSWDMISMATCH 464




#endif
