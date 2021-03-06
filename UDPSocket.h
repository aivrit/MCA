/*
 * UDPSocket.h
 *
 *  Created on: Feb 6, 2013
 *      Author: Eliav Menachi
 */

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include <netinet/in.h>
#include <inttypes.h>
#include <strings.h>
#include <stdio.h>
#include <iostream>
#include "Parser.h"

using namespace std;


class UDPSocket{
	struct sockaddr_in from;
	int socket_fd;
	string listen_port;

public:
	UDPSocket(int port = 9999);
	int recv(char* buffer, int length);
	int sendTo(const string& msg, const string& ip, int port);
	int reply(const string& msg);
	void close();
	string fromAddr();
	string fromPort();
};


#endif /* UDPSOCKET_H_ */
