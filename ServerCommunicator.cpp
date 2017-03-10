/*
 * ServerCommunicator.cpp
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#include "ServerCommunicator.h"

const int PEER_PORT = 3346;
const int MAX_MESSAGE_BYTES = 250;


ServerCommunicator::ServerCommunicator() {
	// TODO Auto-generated constructor stub
	this->tcpsock = NULL;

}

ServerCommunicator::~ServerCommunicator() {
	// TODO Auto-generated destructor stub
}

void ServerCommunicator::connect(string address)
{
	if(!isConnected())
	{
		this->tcpsock = new TCPSocket(address, PEER_PORT);
	}
}

bool ServerCommunicator::isConnected()
{
	return (this->tcpsock != NULL) && (this->tcpsock->socket() != NULL);
}
void ServerCommunicator::listConnectedUsers()
{
	if (this->isConnected())
	{
		string message = numberToString(LIST_CONNECTED_USERS) + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
		vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

		if(parsedData.size() > 1)
		{
			cout << "connected users: " << parsedData[1] << endl;
		}
		else
		{
			cout <<" could not fetch list of connected users" << endl;
		}
	}
	else
	{
		cout << "not connected to server" << endl;
	}
}

void ServerCommunicator::listChatRooms()
{
	if (this->isConnected())
	{
		string message = numberToString(LIST_CHAT_ROOMS) + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
		vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

		if(parsedData.size() > 1)
		{
			cout << "chat rooms: " << parsedData[1] << endl;
		}
		else
		{
			cout <<" could not fetch list of chat rooms" << endl;
		}
	}
	else
	{
		cout << "not connected to server" << endl;
	}
}

void ServerCommunicator::listChatRoomUsers(string roomName)
{
	if (this->isConnected())
	{
		string message = numberToString(LIST_CHAT_ROOM_USERS) + MESSAGE_DELIMITER + roomName + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
		vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

		if(parsedData.size() > 1)
		{
			cout << "users in chat room: " << parsedData[1] << endl;
		}
		else
		{
			cout <<" could not fetch list of users in chat room" << endl;
		}
	}
	else
	{
		cout << "not connected to server" << endl;
	}
}
bool ServerCommunicator::login(string username, string password)
{
	if (this->isConnected())
	{
		string message = numberToString(LOGIN) + MESSAGE_DELIMITER + username + MESSAGE_DELIMITER +
						 password + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
		vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

		if(parsedData[0] == numberToString(SUCCESS))
		{
			cout << "successfully logged in " << endl;
			return true;
		}
		else
		{
			cout <<" failed to login" << endl;
		}
	}
	else
	{
		cout << "not connected to server" << endl;
	}

	return false;
}
bool ServerCommunicator::registerUser(string username, string password)
{
	if (this->isConnected())
	{
		string message = numberToString(REGISTER) + MESSAGE_DELIMITER + username + MESSAGE_DELIMITER +
						 	 	 	 	 	 	 password + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
		vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

		if(parsedData[0] == numberToString(SUCCESS))
		{
			cout << "successfully registered " << endl;
			return true;
		}
		else
		{
			cout <<" failed to register" << endl;
		}
	}
	else
	{
		cout << "not connected to server" << endl;
	}

	return false;
}

string ServerCommunicator::openChat(string username)
{
	if (this->isConnected())
	{
		string message = numberToString(CONNECT_TO_PEER_INIT) + MESSAGE_DELIMITER + username + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
		vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

		if(parsedData.size() > 1)
		{
			return parsedData[1];
		}
	}
	else
	{
		cout << "not connected to server" << endl;
	}

	return "";
}

void ServerCommunicator::listUsers()
{
	if (this->isConnected())
		{
			string message = numberToString(LIST_USERS) + MESSAGE_DELIMITER;
			this->tcpsock->send(message);
			char buffer[MAX_MESSAGE_BYTES];
			this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
			vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

			if(parsedData.size() > 1)
			{
				cout << "users " << parsedData[1] << endl;
			}
			else
			{
				cout <<" could not fetch list of users" << endl;
			}
		}
		else
		{
			cout << "not connected to server" << endl;
		}
}

vector<string> ServerCommunicator::openChatRoom(string roomName)
{
	vector<string> parsedData;
	if (this->isConnected())
		{
			string message = numberToString(JOIN_CHATROOM) + MESSAGE_DELIMITER + roomName + MESSAGE_DELIMITER;
			this->tcpsock->send(message);
			char buffer[MAX_MESSAGE_BYTES];
			this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
			 parsedData = split(buffer, MESSAGE_DELIMITER);
		}
		else
		{
			cout << "not connected to server" << endl;
		}

		return parsedData;
}

bool ServerCommunicator::destroyChatRoom(string roomName)
{
	if (this->isConnected())
		{
			string message = numberToString(DESTROY_CHATROOM) + MESSAGE_DELIMITER + roomName + MESSAGE_DELIMITER;
			this->tcpsock->send(message);
			char buffer[MAX_MESSAGE_BYTES];
			this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
			vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

			if(parsedData[0] == numberToString(SUCCESS))
				return true;
		}
		else
		{
			cout << "not connected to server" << endl;
		}

		return false;
}

bool ServerCommunicator::exitChatRoom()
{
	if (this->isConnected())
	{
		string message = numberToString(EXIT_CHATROOM) + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
		vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

		if(parsedData[0] == numberToString(SUCCESS))
			return true;
	}
	else
	{
		cout << "not connected to server" << endl;
	}

	return false;
}

void ServerCommunicator::disconnect()
{
	if (this->isConnected())
	{
		string message = numberToString(EXIT) + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		this->tcpsock->close();
		delete this->tcpsock;
	}
}

string ServerCommunicator::checkInitChat(string address)
{
	if (this->isConnected())
	{
		string message = numberToString(CONNECT_TO_PEER_RUN) + MESSAGE_DELIMITER + address + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
		vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

		if(parsedData.size() > 1)
		{
			return parsedData[1];
		}
	}
	else
	{
		cout << "not connected to server" << endl;
	}

	return "";
}

bool ServerCommunicator::closeSessionWithPeer()
{
	if (this->isConnected())
	{
		string message = numberToString(CLOSE_SESSION_WITH_PEER) + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
		vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

		if(parsedData[0] == numberToString(SUCCESS))
			return true;
	}
	else
	{
		cout << "not connected to server" << endl;
	}

	return false;
}
