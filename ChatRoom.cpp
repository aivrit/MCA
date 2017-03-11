/*
 * ChatRoom.cpp
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#include "ChatRoom.h"

static const int SEND_PORT = 5001;
static const int RECV_PORT = 9999;

ChatRoom::ChatRoom(vector<string> users, string username) {
	for(vector<string>::size_type i = 1; i < users.size(); i+=2)
	{
	    this->AddressUsernameDict[users[i]] = users[i+1];
	}

	this->udpSocket = new UDPSocket(RECV_PORT);
	this->send(username, JOIN_CHATROOM);
}

ChatRoom::~ChatRoom() {
	// TODO Auto-generated destructor stub
	this->send("", EXIT_CHATROOM);
	delete this->udpSocket;
}

bool ChatRoom::sendMessage(string message)
{
	this->send(message, SEND_MSG_TO_PEER);
	return true;
}

void ChatRoom::recv(string message, int header, string address)
{
	if (header == JOIN_CHATROOM)
	{
		this->AddressUsernameDict[address] = message;
	}
	else if (header == SEND_MSG_TO_PEER)
	{
		cout << "[" << AddressUsernameDict[address] << "]: " <<  message << endl;
	}
	else if (header == EXIT_CHATROOM)
	{
		AddressUsernameDict.erase(address);
	}
}

bool ChatRoom::send(string message, int header)
{
	string message_complete = "";

	for(map<string, string>::value_type& curr : AddressUsernameDict)
	{
		message_complete = numberToString(header) + MESSAGE_DELIMITER + message + MESSAGE_DELIMITER;
		// TODO bad inputs
		this->udpSocket->sendTo(message_complete, curr.first, SEND_PORT);
	}

	return true;
}
