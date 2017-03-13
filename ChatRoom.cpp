/*
 * ChatRoom.cpp
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#include "ChatRoom.h"

static const int SEND_PORT = 0;
static const int RECV_PORT = 9999;

ChatRoom::ChatRoom(vector<string> &users, string username, string listen_port) {
	this->listen_sock = listen_port;
	for(vector<string>::size_type i = 1; i < users.size(); i+=3)
	{
	    this->AddressUsernameDict[users[i]+MESSAGE_DELIMITER+users[i+2]] = users[i+1];
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
	cout << "[Me]: " << message << endl;
	return true;
}

void ChatRoom::recv(string message, int header, string address, string port)
{
	if (header == JOIN_CHATROOM)
	{
		this->AddressUsernameDict[address+MESSAGE_DELIMITER+port] = message;
	}
	else if (header == SEND_MSG_TO_PEER)
	{
		cout << "[" << AddressUsernameDict[address+MESSAGE_DELIMITER+port] << "]: " <<  message << endl;
	}
	else if (header == EXIT_CHATROOM)
	{
		AddressUsernameDict.erase(address+MESSAGE_DELIMITER+port);
	}
}

bool ChatRoom::send(string message, int header)
{
	string message_complete = numberToString(header) + MESSAGE_DELIMITER + this->listen_sock + MESSAGE_DELIMITER +
							  message + MESSAGE_DELIMITER;

	if (!AddressUsernameDict.empty())
	{
		for (std::map<string,string>::iterator it=AddressUsernameDict.begin(); it!=AddressUsernameDict.end(); ++it)
		{
			vector<string> ip_port = split(it->first, MESSAGE_DELIMITER);
			this->udpSocket->sendTo(message_complete, ip_port[0], atoi(ip_port[1].c_str()));
		}
	}
	return true;
}
