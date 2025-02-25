/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RplMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:58 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/25 12:48:43 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPLMESSAGE_HPP
#define RPLMESSAGE_HPP

#include <iostream>
#include <vector>
#include <cstdarg>
#include <sys/socket.h>

class RplMessage
{
	public:

		static void GetRply(int code, int fd, int size, const char * value, ...);
};

#endif
