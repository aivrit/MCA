/*
 * UserChat.h
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#ifndef USERCHAT_H_
#define USERCHAT_H_

#include <string>
#include "UDPSocket.h"
#include "MessageHeaders.cpp"
#include <ctime>
#include "Parser.h"
#include <stdlib.h>

using namespace std;

class UserChat {
public:
	UserChat(string address, string username, string port, string user_port);
	virtual ~UserChat();
	bool initiateChat();
	bool sendMessage(string message);
	void recv(string message, int header, string address, string port);
	bool send(string message, int header);
	void acceptChat();

private:
	UDPSocket* udpSocket;
	string address;
	int status;
	string username;
	string listen_port;
	string user_port;
};

#endif /* USERCHAT_H_ */
