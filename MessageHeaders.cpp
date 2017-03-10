/*
 * MessageHeaders.cpp
 *
 *  Created on: 25 Feb 2017
 *      Author: alon
 */

#ifndef MESSAGEHEADERS
#define MESSAGEHEADERS

const char  MESSAGE_DELIMITER = ';';
const int	SEND_MSG_TO_PEER = 1;
const int   CONNECT_TO_PEER_RUN = 2;
const int   CONNECT_TO_PEER_INIT = 3;
const int   CLOSE_SESSION_WITH_PEER = 4;
const int   LIST_CONNECTED_USERS = 5;
const int   LIST_CHAT_ROOMS = 6;
const int   LOGIN = 7;
const int   SUCCESS = 8;
const int   FAILURE = 9;
const int   REGISTER = 10;
const int   EXIT = 11;
const int   JOIN_CHATROOM = 12;
const int   CREATE_CHATROOM = 13;
const int   LIST_USERS = 14;
const int   EXIT_CHATROOM = 15;
const int   DESTROY_CHATROOM = 16;
const int   LIST_CHAT_ROOM_USERS = 17;

static const int NO_OPEN_SESSION = 0;
static const int OPEN_USER_CHAT = 1;
static const int OPEN_CHAT_ROOM = 2;

#endif /* MESSAGEHEADERS */
