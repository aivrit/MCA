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

using namespace std;

class UserChat {
public:
	UserChat(string address, string username);
	virtual ~UserChat();
	bool initiateChat();
	bool sendMessage(string message);
	void recv(string message, int header, string address);
	bool send(string message, int header);
	void acceptChat();

private:
	UDPSocket* udpSocket;
	string address;
	int status;
	string username;
};

#endif /* USERCHAT_H_ */
