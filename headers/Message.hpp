/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:52 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/05 23:32:30 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>
#include <sstream>

class Message
{
public:
	Message();
	Message(std::string buffer);

	const std::string &getCommand() const;
	const std::string &getTarget() const;
	std::string &getParameter();
	const std::string &getSuffix() const;

	void parseNICK_USER_PASS(void);
	void parseWHO(void);
	void parsePRIVMSG_PART_TOPIC(void);
	void parseQUIT(void);

	void parseJOIN(void); // TO BE CONTINUED
	void parseKICK(void); // TO BE CONTINUED

	// void	parseINVITE(void);
	// void	parseMODE(void);

	void	parseCHESS(void);

private:
	void msgchess(std::vector<std::string> _words, unsigned long i);
	std::vector<std::string> _words;
	std::string _prefix; //  std::string prefix = ":" + clientNick + "!" + clientUser + "@" + clientHost;
	std::string _command;
	std::string _target;
	std::string _parameter;
	std::string _suffix;
};

#endif
