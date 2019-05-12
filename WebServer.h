#pragma once


#pragma once
#include "TcpListener.h"

class WebServer : public TcpListener
{
public:
	char username[64][64];
	char password[64][64];
	int num;
	WebServer(const char* ipAddress, int port) :
		TcpListener(ipAddress, port) { }

protected:

	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	// Handler for when a message is received from the client
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);

public: 
	void openFile();
};