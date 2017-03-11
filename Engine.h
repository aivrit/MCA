/*
 * Engine.h
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <pthread.h>
#include <vector>
#include <string>
#include <sstream>
#include "ChatRoom.h"
#include "UserChat.h"
#include "ServerCommunicator.h"
#include "Parser.h"

class UDPListener;

using namespace std;

class Engine {
public:
	Engine();
	virtual ~Engine();
	void run();
	void printHelp();
	void listUsers();
	bool connectToServer(string address);
	void listConnectedUsers();
	void listChatRooms();
	void listChatRoomUsers(string roomName);
	bool login(string username, string password);
	bool registerUser(string username, string password);
	bool openChat(string username);
	bool openChatRoom(string roomName);
	bool sendMessage(string message);
	void listStatus();
	void disconnectServer();
	void disconnectChat();
	bool initiateChatRoom(string roomName);
	bool destroyChatRoom(string roomName);
	void acceptChat(string address);
	UDPListener* getUdpListener();
	int getStatus();
	UserChat* getUserChat();
	ChatRoom* getChatRoom();

private:
	int status;
	UDPListener* udpListener;
	ChatRoom* chatRoom;
	UserChat* userChat;
	ServerCommunicator* serverCommunicator;
	string username;

};

#endif /* ENGINE_H_ */
