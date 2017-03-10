/*
 * ServerCommunicator.h
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#ifndef SERVERCOMMUNICATOR_H_
#define SERVERCOMMUNICATOR_H_
#include <string>
#include "MessageHeaders.cpp"
#include "Parser.h"
#include "TCPSocket.h"
#include <vector>

using namespace std;

class ServerCommunicator {
public:
	ServerCommunicator();
	virtual ~ServerCommunicator();
	void connect(string address);
	bool isConnected();
	void listConnectedUsers();
	void listChatRooms();
	void listChatRoomUsers(string roomName);
	bool login(string username, string password);
	bool registerUser(string username, string password);
	string openChat(string username);
	vector<string> openChatRoom(string roomName);
	void disconnect();
	string checkInitChat(string address);
	bool closeSessionWithPeer();
	void listUsers();
	bool destroyChatRoom(string roomName);
	bool exitChatRoom();

private:
	TCPSocket* tcpsock;
};

#endif /* SERVERCOMMUNICATOR_H_ */
