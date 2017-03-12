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
		if(this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES > 0))
		{
			vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

			if(parsedData[0] == numberToString(SUCCESS))
			{
				string message = "";
				for (int i=1; i<parsedData.size(); i++)
				{
					message += parsedData[i] + " : ";
				}
				cout << "connected users : " << message << endl;
			}
			else
			{
				cout <<" could not fetch list of connected users" << endl;
			}
		}
		else
		{
			cout << "could not fetch list of connected users. timed out waiting for server" << endl;
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
		if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0)
		{
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
			cout <<" could not fetch list of chat rooms. timed out on server." << endl;
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
		if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0)
		{
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
			cout <<" could not fetch list of users in chat room. timed out on server." << endl;
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
		if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0)
		{
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
			cout <<" failed to login. timed out on server." << endl;
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
		memset(buffer,0, sizeof(buffer));
		if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0)
		{
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
			cout <<" failed to register. timed out on server." << endl;
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
		if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0 )
		{
			vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

			if(parsedData[0] == numberToString(SUCCESS) && parsedData.size() > 1)
			{
				return parsedData[1];
			}
		}
		else
		{
			cout << "error opening chat. timed out on server." << endl;
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
			int length = this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
			if (length > 0)
			{
				buffer[length] = '\0';
				vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

				if(parsedData.size() > 1)
				{
					cout << "users: " << endl;
					for(int i=1;i<parsedData.size();i++)
					{
						cout <<  parsedData[i] << endl;
					}
				}
				else
				{
					cout <<" could not fetch list of users" << endl;
				}
			}
			else
			{
				cout <<" could not fetch list of users. timed out on server." << endl;
			}
		}
		else
		{
			cout << "not connected to server" << endl;
		}
}

bool ServerCommunicator::openChatRoom(string roomName, char* buffer)
{
	if (this->isConnected())
		{
			string message = numberToString(JOIN_CHATROOM) + MESSAGE_DELIMITER + roomName + MESSAGE_DELIMITER;
			this->tcpsock->send(message);
			int len = this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES);
			if (len > 0)
			{
				buffer[len] = '\0';
				return true;
			}
			else
			{
				cout << "error opening chat room. timed out on server. " << endl;
			}
		}
		else
		{
			cout << "not connected to server" << endl;
		}

		return false;;
}

bool ServerCommunicator::destroyChatRoom(string roomName)
{
	if (this->isConnected())
		{
			string message = numberToString(DESTROY_CHATROOM) + MESSAGE_DELIMITER + roomName + MESSAGE_DELIMITER;
			this->tcpsock->send(message);
			char buffer[MAX_MESSAGE_BYTES];
			if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0)
			{
				vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

				if(parsedData[0] == numberToString(SUCCESS))
					return true;
			}
			else
			{
				cout << "error destroying chat room. timed out on server." << endl;
			}
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
		if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0)
		{
			vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

			if(parsedData[0] == numberToString(SUCCESS))
			{
				cout << "exited chat room" << endl;
				return true;
			}
			else
			{
				cout << "error exiting chat room." << endl;
			}
		}
		else
		{
			cout << "error exiting chat room. timed out on server." << endl;
		}
	}
	else
	{
		cout << "not connected to server" << endl;
	}

	return false;
}

bool ServerCommunicator::initiateChatRoom(string roomName)
{
	if (this->isConnected())
	{
		string message = numberToString(CREATE_CHATROOM) + MESSAGE_DELIMITER + roomName + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0)
		{
			vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

			if(parsedData[0] == numberToString(SUCCESS))
				return true;
		}
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
		this->tcpsock = NULL;
	}
}

string ServerCommunicator::checkInitChat(string address)
{
	if (this->isConnected())
	{
		string message = numberToString(CONNECT_TO_PEER_RUN) + MESSAGE_DELIMITER + address + MESSAGE_DELIMITER;
		this->tcpsock->send(message);
		char buffer[MAX_MESSAGE_BYTES];
		if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0)
		{
			vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

			if(parsedData.size() > 1)
			{
				return parsedData[1];
			}
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
		if (this->tcpsock->recv(buffer, MAX_MESSAGE_BYTES) > 0)
		{
			vector<string> parsedData = split(buffer, MESSAGE_DELIMITER);

			if(parsedData[0] == numberToString(SUCCESS))
				return true;
		}
	}
	else
	{
		cout << "not connected to server" << endl;
	}

	return false;
}
