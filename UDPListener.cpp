/*
 * UDPListener.cpp
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#include "UDPListener.h"

static const int LISTEN_PORT = 0;
static const int MAX_MESSAGE_BYTES = 250;

void flushBuffer(char* buffer)
{
	for(int i=0;i<sizeof(buffer); i++)
	{
		buffer[i] = '\0';
	}
}

UDPListener::UDPListener() {
	// TODO Auto-generated constructor stub
	this->udpsock = new UDPSocket(LISTEN_PORT);

}

UDPListener::~UDPListener() {
	// TODO Auto-generated destructor stub
	delete this->udpsock;
}

void UDPListener::run(Engine* engine)
{
	char buffer[MAX_MESSAGE_BYTES];
	int recvlen;
	vector<string> parsedData;
	int header;

	while(true)
	{
		recvlen = this->udpsock->recv(buffer, MAX_MESSAGE_BYTES);
		//cout << "recieved: " << buffer << endl;
		if (recvlen > 0)
		{
			// michael needs to send me the delimiter after the message too!
			parsedData = split(buffer, MESSAGE_DELIMITER);

			header = atoi(parsedData[0].c_str());

			 if (engine->getStatus() == OPEN_USER_CHAT)
			 {
				 if (parsedData.size() > 2)
					 engine->getUserChat()->recv(parsedData[2], header, this->udpsock->fromAddr(), parsedData[1]);
			 }
			 else if (engine->getStatus() == OPEN_CHAT_ROOM)
			 {
				 	 if (parsedData.size() > 2)
				 		 engine->getChatRoom()->recv(parsedData[2], header, this->udpsock->fromAddr(), parsedData[1]);
			 }
			 else if(engine->getStatus() == NO_OPEN_SESSION)
			 {
				 if (header == CONNECT_TO_PEER_INIT)
				 {
					 if (parsedData.size() > 1)
					 engine->acceptChat(this->udpsock->fromAddr(), parsedData[1]);
				 }
				 else if (header == CONNECT_TO_PEER_RUN && engine->getUserChat() != NULL)
				 {
					 if (parsedData.size() > 1)
						 engine->getUserChat()->recv("", header, this->udpsock->fromAddr(), parsedData[1]);
				 }
			 }
		}

		flushBuffer(buffer);
	}

}

string UDPListener::get_listen_port()
{
	//cout << "listen port: " << this->udpsock->fromPort();
	return this->udpsock->fromPort();
}
