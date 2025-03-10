/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:45 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/24 12:14:50 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "Server.hpp"
#include "Poll.hpp"

int main (void)
{
	TRY(
	Server launch;

	Poll poll(&launch);
	poll.Start();
	return 0;
	)
}
