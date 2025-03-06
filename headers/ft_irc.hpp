
#ifndef FT_IRC_HPP
# define FT_IRC_HPP

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

#endif
