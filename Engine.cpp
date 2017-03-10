/*
 * Engine.cpp
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#include "UDPListener.h"
#include "Engine.h"


void* runUdpListener(void* arg)
{
	Engine* engine = (Engine*)arg;
	UDPListener* listener = engine->getUdpListener();
	listener->run(engine);
	pthread_exit(NULL);
}

Engine::Engine() {
	// TODO Auto-generated constructor stub
	this->chatRoom = NULL;
	this->userChat = NULL;
	this->status = NO_OPEN_SESSION;
	this->serverCommunicator = new ServerCommunicator();
	this->udpListener = new UDPListener();
	this->username = "";

	pthread_t ithread[1];

	// run dispatcher and listener in different threads
	pthread_create(&ithread[0], NULL, runUdpListener, (void*)this);
	//pthread_create(&ithread[1], NULL, runServerCommunicator, NULL);

}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
	delete this->serverCommunicator;
	delete this->udpListener;
}

UserChat* Engine::getUserChat()
{
	return this->userChat;
}

int Engine::getStatus()
{
	return this->status;
}

UDPListener* Engine::getUdpListener()
{
	return this->udpListener;
}

void Engine::run()
{
	cout << "welcome to MCA" << endl;

	char userData[100];

	cin.getline(userData,sizeof(userData));

	std::vector<std::string> parsedData = split(userData, ' ');

	// continue program until user exits
	while(parsedData[0] != "x")
	{
		// print peers
		if(parsedData[0] == "c")
		{
			if (parsedData.size() >= 2)
			{
				this->connectToServer((string)parsedData[1]);
			}
			else
			{
				this->printHelp();
			}
		}
		else if (parsedData[0] == "lu")
		{
			this->listUsers();
		}
		else if (parsedData[0] == "lcu")
		{
			this->listConnectedUsers();
		}
		else if (parsedData[0] == "lr")
		{
			this->listChatRooms();
		}
		else if (parsedData[0] == "lru")
		{
			if (parsedData.size() >= 2)
			{
				this->listChatRoomUsers((string)parsedData[1]);
			}
			else
			{
				this->printHelp();
			}
		}
		else if (parsedData[0] == "login")
		{
			if (parsedData.size() >= 3)
			{
				this->login((string)parsedData[1], (string)parsedData[2]);
			}
			else
			{
				this->printHelp();
			}
		}
		else if (parsedData[0] == "register")
		{
			if (parsedData.size() >= 3)
			{
				this->registerUser((string)parsedData[1], (string)parsedData[2]);
			}
			else
			{
				this->printHelp();
			}
		}
		else if (parsedData[0] == "o")
		{
			if (parsedData.size() >= 2)
			{
				this->openChat((string)parsedData[1]);
			}
			else
			{
				this->printHelp();
			}
		}
		else if (parsedData[0] == "or")
		{
			if (parsedData.size() >= 2)
			{
				this->openChatRoom((string)parsedData[1]);
			}
			else
			{
				this->printHelp();
			}
		}
		else if (parsedData[0] == "s")
		{
			if (parsedData.size() >= 2)
			{
				this->sendMessage((string)parsedData[1]);
			}
			else
			{
				this->printHelp();
			}
		}
		else if (parsedData[0] == "l")
		{
			this->listStatus();
		}
		else if (parsedData[0] == "cs")
		{
			this->disconnectChat();
		}
		else if (parsedData[0] == "ir")
		{
			if (parsedData.size() >= 2)
			{
				this->initiateChatRoom((string)parsedData[1]);
			}
			else
			{
				this->printHelp();
			}
		}
		else if (parsedData[0] == "cr")
		{
			if (parsedData.size() >= 2)
			{
				this->destroyChatRoom((string)parsedData[1]);
			}
			else
			{
				this->printHelp();
			}
		}
		else if (parsedData[0] == "d")
		{
			this->disconnectServer();
		}
		else
		{
			this->printHelp();
		}

		cin.getline(userData,sizeof(userData));
		parsedData = split(userData, ' ');
	}
}

void Engine::printHelp()
{
	cout << "-----------------------------------------------" << endl;
	cout << "c <server_ip> - connect to server" << endl;
	cout << "lu - print user list from the server" << endl;
	cout << "lcu - print connected users list from the server" << endl;
	cout << "lr - print all chat rooms in server" << endl;
	cout << "lru <room_name> - print user list of a room" << endl;
	cout << "login <user_name> <password> - login" << endl;
	cout << "register <user_name> <password> - register" << endl;
	cout << "o <user_name> - open a chat session with a user" << endl;
	cout << "or <room_name> - enter a chat room" << endl;
	cout << "s <message> - send a message" << endl;
	cout << "l - print status" << endl;
	cout << "cs - disconnect from chat" << endl;
	cout << "ir <room_name> - initiate a chat room" << endl;
	cout << "cr <room_name> - close a chat room you initiated" << endl;
	cout << "d - disconnect from server" << endl;
	cout << "x - close MCA" << endl;
	cout << "-----------------------------------------------" << endl;
}

void Engine::listUsers()
{
	if (this->serverCommunicator->isConnected())
		{
			this->serverCommunicator->listUsers();
		}
		else
		{
			cout << "error: not connected to a server" << endl;
		}
}

bool Engine::connectToServer(string address)
{
	if (!this->serverCommunicator->isConnected())
	{
		this->serverCommunicator->connect(address);
		return true;
	}
	else
	{
		cout << "error: already connected to a server" << endl;

		return false;
	}
}

void Engine::listConnectedUsers()
{
	if (this->serverCommunicator->isConnected())
	{
		this->serverCommunicator->listConnectedUsers();
	}
	else
	{
		cout << "error: not connected to a server" << endl;
	}
}

void Engine::listChatRooms()
{
	if (this->serverCommunicator->isConnected())
	{
		this->serverCommunicator->listChatRooms();
	}
	else
	{
		cout << "error: not connected to a server" << endl;
	}
}

void Engine::listChatRoomUsers(string roomName)
{
	if (this->serverCommunicator->isConnected())
	{
		this->serverCommunicator->listChatRoomUsers(roomName);
	}
	else
	{
		cout << "error: not connected to a server" << endl;
	}
}

bool Engine::login(string username, string password)
{
	if (this->serverCommunicator->isConnected())
	{
		this->username = username;
		return this->serverCommunicator->login(username, password);
	}
	else
	{
		cout << "error: not connected to a server" << endl;
		return false;
	}
}

bool Engine::registerUser(string username, string password)
{
	if (this->serverCommunicator->isConnected())
	{
		return this->serverCommunicator->registerUser(username, password);
	}
	else
	{
		cout << "error: not connected to a server" << endl;
		return false;
	}
}

bool Engine::openChat(string username)
{
	if (this->status == NO_OPEN_SESSION)
	{
		string address = this->serverCommunicator->openChat(username);

		if (username != "")
		{
			this->userChat = new UserChat(address, username);
			if (this->userChat->initiateChat())
			{
				this->status = OPEN_USER_CHAT;
				cout << "you are now in chat with " << username << endl;
				return true;
			}
			else
			{
				cout << "user" << username << "refused connection or is not active" << endl;
			}
		}
		else
		{
			cout << "problem starting chat with" << username << endl;
		}
	}
	else
	{
		cout << "already in chat" << endl;
	}

	return false;
}

bool Engine::openChatRoom(string roomName)
{
	if (this->status == NO_OPEN_SESSION)
	{
		vector<string> roomUsersList = this->serverCommunicator->openChatRoom(roomName);

		if(roomUsersList.size() > 0)
		{
			cout << "error opening chat room" << endl;
			return false;
		}

		this->chatRoom = new ChatRoom(roomUsersList, this->username);
		this->status = OPEN_CHAT_ROOM;
		cout << "you are now in chat room " << roomName << endl;
		return true;

	}
	else
	{
		cout << "already in chat" << endl;
	}

	return false;
}

bool Engine::sendMessage(string message)
{
	if (this->status == NO_OPEN_SESSION)
	{
		cout << "not connected to server" << endl;
		return false;
	}
	else if (this->status == OPEN_USER_CHAT)
	{
		if (this->userChat->sendMessage(message))
		{
			return true;
		}
		else
		{
			cout << "problem sending message" << endl;
			return false;
		}

	}
	else if (this->status == OPEN_CHAT_ROOM)
	{

	}

	return true;
}

void Engine::listStatus()
{
}

void Engine::disconnectServer()
{
	if (this->status != NO_OPEN_SESSION)
	{
		cout << "to disconnect you have to exit you chat first" << endl;
	}
	else
	{
		this->serverCommunicator->disconnect();
	}
}

void Engine::disconnectChat()
{
	if(this->status == OPEN_USER_CHAT)
	{
		this->serverCommunicator->closeSessionWithPeer();
		delete this->userChat;
		this->userChat = NULL;
		this->status = NO_OPEN_SESSION;
	}
	else if(this->status == OPEN_CHAT_ROOM)
	{
		this->serverCommunicator->exitChatRoom();
		delete this->chatRoom;
		this->chatRoom = NULL;
		this->status = NO_OPEN_SESSION;
	}
	else
	{
		cout << "cannot disconnect from chat because no chat is open" << endl;
	}
}

bool Engine::initiateChatRoom(string roomName)
{
	return true;
}

bool Engine::destroyChatRoom(string roomName)
{
	if (this->serverCommunicator->destroyChatRoom(roomName))
		cout << "successfully destroyed chat room " << roomName << endl;

	return true;
}

void Engine::acceptChat(string address)
{
	string username = this->serverCommunicator->checkInitChat(address);

	if (username != "")
	{
		this->userChat = new UserChat(address, username);
		this->userChat->acceptChat();
		this->status = OPEN_USER_CHAT;
	}
}
