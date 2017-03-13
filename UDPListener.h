/*
 * UDPListener.h
 *
 *  Created on: 24 Feb 2017
 *      Author: alon
 */

#ifndef UDPLISTENER_H_
#define UDPLISTENER_H_

#include "UDPSocket.h"
#include "MessageHeaders.cpp"
#include <string>
#include <vector>
#include "Parser.h"
#include "Engine.h"
#include <stdlib.h>

using namespace std;



class UDPListener {
public:
	UDPListener();
	virtual ~UDPListener();
	void run(Engine* engine);
	string get_listen_port();
private:
	UDPSocket* udpsock;
};

#endif /* UDPLISTENER_H_ */
