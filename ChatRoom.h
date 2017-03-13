/*
 * ChatRoom.h
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#ifndef CHATROOM_H_
#define CHATROOM_H_

#include <string>
#include <map>
#include <vector>
#include "UDPSocket.h"
#include "MessageHeaders.cpp"
#include "Parser.h"
#include <stdlib.h>


using namespace std;

class ChatRoom {
public:
	ChatRoom(vector<string> &users, string username, string listen_port);
	virtual ~ChatRoom();
	bool sendMessage(string message);
	void recv(string message, int header, string address, string port);
	bool send(string message, int header);
private:
	map<string, string> AddressUsernameDict;
	UDPSocket* udpSocket;
	string listen_sock;
};

#endif /* CHATROOM_H_ */
