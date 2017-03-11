/*
 * UserChat.cpp
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#include "UserChat.h"

static const int SEND_PORT = 5001;
static const int RECV_PORT = 9999;
static const int STATUS_NO_CHAT = 0;
static const int STATUS_INITIATING = 1;
static const int STATUS_INITIATED = 2;

UserChat::UserChat(string address, string username) {
	this->udpSocket = new UDPSocket(RECV_PORT);
	this->address = address;
	this->status = STATUS_NO_CHAT;
	this->username = username;
}

UserChat::~UserChat() {
	// TODO Auto-generated destructor stub
	delete this->udpSocket;

}

bool UserChat::sendMessage(string message)
{
	if (this->send(message, SEND_MSG_TO_PEER))
	{
		cout << "[Me]: " << message << endl;
		return true;
	}

	return false;
}

bool UserChat::send(string message, int header)
{
	string message_complete = numberToString(header) + MESSAGE_DELIMITER + message + MESSAGE_DELIMITER;
	// TODO bad inputs
	if (this->udpSocket->sendTo(message_complete, address, SEND_PORT) == -1)
		return false;

	cout << "sent to : " << address << ":" << numberToString(SEND_PORT) << " message: "
			<< message_complete << endl;
	return true;
}

bool UserChat::initiateChat()
{
	const int timeout_sec = 20;
	time_t start_time = time(0);

	this->status = STATUS_INITIATING;
	if (!this->send("", CONNECT_TO_PEER_INIT))
		return false;

	while (this->status != STATUS_INITIATED && start_time + timeout_sec > time(0))
	{
		// wait
	}

	return this->status == STATUS_INITIATED;
}

void UserChat::acceptChat()
{
	this->send("", CONNECT_TO_PEER_RUN);
	this->status = STATUS_INITIATED;
}


void UserChat::recv(string message, int header, string address)
{
	if (this->status == STATUS_INITIATED && address == this->address)
	{
		if (header == SEND_MSG_TO_PEER)
		{
			cout << "[" << this->username <<  "]: " << message << endl;
		}
		else if (header == CLOSE_SESSION_WITH_PEER)
		{
			cout << "peer closed chat. press x to exit." << endl;
		}
	}
	else if (this->status == STATUS_INITIATING && address == this->address &&
			 header == CONNECT_TO_PEER_RUN)
	{
		this->status = STATUS_INITIATED;
	}
}

