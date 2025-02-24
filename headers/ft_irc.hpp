/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:50 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/24 12:13:51 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include <cstdio>

#define TRY(expression) \
try \
{ \
    expression; \
} \
catch(const std::exception& e) \
{ \
    std::cerr << e.what() << std::endl; \
}
